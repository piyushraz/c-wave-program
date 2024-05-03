#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEADER_SIZE 22
#define DEFAULT_DELAY 8000
#define DEFAULT_VOLUME_SCALE 4
#define SAMPLING_RATE 22050

int main(int argc, char *argv[]) {

    int delay = DEFAULT_DELAY;
    int volume_scale = DEFAULT_VOLUME_SCALE;
    char *source_wav, *dest_wav;
    unsigned int *sizeptr;
    short *buffer;
    short header[HEADER_SIZE];
    int option;
    short sample;
    while ((option = getopt(argc, argv, "d:v:")) != -1) {
 
        switch (option) {
 
            case 'd': 
            {
                char *delay_check;
                delay = strtol(optarg, &delay_check, 10);
                if (optarg == delay_check || *delay_check != '\0') {
                    printf("Error: No numeric value for delay -d passed\n");
                    return 1;
                }
                if (delay < 0) {
                    printf("Error: Invalid value for delay\n");
                    return 1;
                }
                break;
            }
            case 'v':
            {
                char *scale_check;
                volume_scale = strtol(optarg, &scale_check, 10);
                if (optarg == scale_check || *scale_check != '\0') {
                    printf("Error: No numeric value for volume scale -v passed\n");
                    return 1;
                }
                if (volume_scale <= 0) {
                    printf("Error: Invalid value for volume scale\n");
                    return 1;
                }
                break;
            }
            default:
                printf("Error: Numeric value d or v not passed correctly\n");
                return 1;
 
        }
    }

    if (argv[optind] != NULL && argv[optind + 1] != NULL) {
        source_wav = argv[optind];      
        dest_wav = argv[optind + 1];    
    } else {
        fprintf(stderr, "Error: File arguments incorrect or missing\n");
        return 1;
    }

    FILE *input_wav = fopen(source_wav, "rb");
    if (input_wav == NULL) {
        fprintf(stderr, "Error: could not open input file\n");
        return 1;
    }

    FILE *output_wav = fopen(dest_wav, "wb");
    if (output_wav == NULL) {
        fprintf(stderr, "Error: could not open output file\n");
        return 1;
    }

    fread(header, sizeof(short), HEADER_SIZE, input_wav);

    sizeptr = (unsigned int *)(header + 2);
    *sizeptr += delay * 2;
    sizeptr = (unsigned int *)(header + 20);
    *sizeptr += delay * 2;

    fwrite(header, sizeof(short), HEADER_SIZE, output_wav);

    buffer = malloc(delay * sizeof(short));

    for (int i = 0; i < delay; i++) {
        buffer[i] = 0;
    }

    int acc = 0;
    while (fread(&sample, sizeof(short), 1, input_wav) == 1) {
        short set_sample_echo = buffer[acc % delay] / volume_scale;
        int mixing_sample = sample + set_sample_echo;
        if (mixing_sample > 32767) {
            mixing_sample = 32767;
        } else if (mixing_sample < -32768) {
            mixing_sample = -32768;
        }
        fwrite(&mixing_sample, sizeof(short), 1, output_wav);
        buffer[acc % delay] = sample;
        acc += 1;
    }

    for (int j = 0; j < delay; j++) {
        short set_sample_echo = buffer[(acc + j) % delay] / volume_scale;
        if (set_sample_echo > 32767) {
            set_sample_echo = 32767;
        } else if (set_sample_echo < -32768) {
            set_sample_echo = -32768;
        }
        fwrite(&set_sample_echo, sizeof(short), 1, output_wav);
    }

    free(buffer);
    fclose(input_wav);
    fclose(output_wav);

    return 0;
}