#include "audio.h"
#include <stdio.h>
#include <alsa/asoundlib.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BUFFER_SIZE 1024

//Dataflow: Application → ALSA → Hardware
int audio_playback_test(void) {
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    short buffer[BUFFER_SIZE * CHANNELS];
    int err;

    if ((err = snd_pcm_open(&handle, "hw:0,0", SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        fprintf(stderr, "Playback open error: %s\n", snd_strerror(err));
        return err;
    }

    //Configuration
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, CHANNELS);
    unsigned int rate = SAMPLE_RATE;
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
    snd_pcm_hw_params(handle, params);
    snd_pcm_hw_params_free(params);

    // Generate sine wave buffer
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        float sample = 0.2f * sinf(2.0f * M_PI * 440.0f * i / SAMPLE_RATE);
        buffer[i * 2] = (short)(sample * 32767);
        buffer[i * 2 + 1] = (short)(sample * 32767);
    }

    for (int i = 0; i < 10; ++i) {
        err = snd_pcm_writei(handle, buffer, BUFFER_SIZE);
        if (err == -EPIPE) {
            // Buffer underrun
            snd_pcm_prepare(handle);
        } else if (err < 0) {
            fprintf(stderr, "Write error: %s\n", snd_strerror(err));
        }
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    return 0;
}


//Data flow: Hardware → ALSA → Application
int audio_record_test(void) {
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    short buffer[BUFFER_SIZE * CHANNELS];
    int err;

    if ((err = snd_pcm_open(&handle, "hw:0,0", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        fprintf(stderr, "Capture open error: %s\n", snd_strerror(err));
        return err;
    }

    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, CHANNELS);
    unsigned int rate = SAMPLE_RATE;
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
    snd_pcm_hw_params(handle, params);
    snd_pcm_hw_params_free(params);

    printf("Start recording 5 buffers...\n");
    for (int i = 0; i < 5; ++i) {
        err = snd_pcm_readi(handle, buffer, BUFFER_SIZE);
        if (err == -EPIPE) {
            // Buffer overrun
            snd_pcm_prepare(handle);
        } else if (err < 0) {
            fprintf(stderr, "Read error: %s\n", snd_strerror(err));
        } else {
            printf("Buffer %d: first samples L=%d R=%d\n", i, buffer[0], buffer[1]);
        }
    }

    snd_pcm_close(handle);
    return 0;
}
