#include <stdio.h>
#include "audio.h"

int main(void) {
    printf("Starting playback test...\r\n");
    if (audio_playback_test() != 0) {
        fprintf(stderr, "Playback test failed!\r\n");
        return 1;
    }

    printf("Playback test finished.\r\n");

    printf("Starting record test...\r\n");
    if (audio_record_test() != 0) {
        fprintf(stderr, "Record test failed!\r\n");
        return 1;
    }

    printf("Record test finished.\r\n");
    return 0;
}
