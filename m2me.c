//
// Created by Jonas on 20.12.2015.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "byte_order.h"
#include "wave.h"

const int INSTRUMENT_SIZE = 12;

typedef struct {
    uint32_t start;
    unsigned short loop, end;
    uint8_t lfo, vib, ar, d1r, dl, d2r, rate_correction, rr, am;
} Instrument;

Instrument *make_instrument() {
    Instrument *i = malloc(sizeof(Instrument));
    return i;
}


void read_instrument(int id, FILE *f, Instrument *i) {
    fseek(f, id * INSTRUMENT_SIZE, SEEK_SET);
    int buffer = 0;
    fread(&i->start, 3, 1, f);
    i->start = (uint32_t) reverseInt24(i->start);
    fread(&i->loop, 2, 1, f);
    i->loop = (unsigned short) reverseShort(i->loop);
    fread(&buffer, 2, 1, f);
    i->end = (unsigned short) (buffer);
    i->end = (unsigned short) (~reverseShort(i->end) + 1);
    fread(&buffer, 1, 1, f);
    i->lfo = (uint8_t) ((buffer >> 3) & 0x07);
    i->vib = (uint8_t) (buffer & 0x07);
    fread(&buffer, 1, 1, f);
    i->ar = (uint8_t) ((buffer >> 4) & 0x0F);
    i->d1r = (uint8_t) (buffer & 0x0F);
    fread(&buffer, 1, 1, f);
    i->dl = (uint8_t) ((buffer >> 4) & 0x0F);
    i->d2r = (uint8_t) (buffer & 0x0F);
    fread(&buffer, 1, 1, f);
    i->rate_correction = (uint8_t) ((buffer >> 4) & 0x0F);
    i->rr = (uint8_t) (buffer & 0x0F);
    fread(&buffer, 1, 1, f);
    i->am = (uint8_t) (buffer & 0x07);
}

void write_instrument(int id, FILE *f, Instrument *i) {
    char str[20];
    sprintf(str, "%03i.wav", id);
    FILE *out = fopen(str, "wb");

    char *data = malloc(i->end);
    fseeko64(f, i->start, SEEK_SET);
    fread(data, i->end, 1, f);
    for (int j = 0; j < i->end; j++) {
        if (data[j] >= 128) {
            data[j] += 127;
        } else {
            data[j] -= 128;
        }
    }

    fwrite(make_WaveHeader(1, 44100, 8, i->end), sizeof(WaveHeader), 1, out);
    fwrite(data, i->end, 1, out);
    if (ftell(out) & 1) fwrite(make_WavePadding(), sizeof(char), 1, out);
    fwrite(make_WaveSmplChunk(), sizeof(WaveSmplChunk), 1, out);
    fwrite(make_WaveSampleLoop(0, 0, i->loop, i->end, 0, 0), sizeof(WaveSampleLoop), 1, out);
    /*fwrite(make_WaveXtraChunk(), sizeof(WaveXtraChunk), 1, out);
    fwrite(make_WaveListChunk(44), sizeof(WaveListChunk), 1, out);
    fwrite(make_WaveChunk(0x4D414E49, 3), sizeof(WaveChunk), 1, out);
    char inam[3] = {'5', '5', '\0'};
    fwrite(inam, 3, 1, out);
    if (ftell(out) & 1)
        fwrite(make_WavePadding(), sizeof(WavePadding), 1, out);
    fwrite(make_WaveChunk(0x54465349, 19), sizeof(WaveChunk), 1, out);
    char openMpt[19] = {'O', 'p', 'e', 'n', 'M', 'P', 'T', ' ', '1', '.', '2', '5', '.', '0', '4', '.', '0', '0'};
    fwrite(openMpt, 19, 1, out);
    if (ftell(out) & 1) fwrite(make_WavePadding(), sizeof(char), 1, out);*/
    fclose(out);
}

void print_instrument(Instrument *i) {
    printf("%8i | %5i | %5i | %2i | %2i | %2i | %2i | %2i | %2i | %2i | %2i | %2i\n",
           i->start,
           i->loop,
           i->end,
           i->lfo,
           i->vib,
           i->ar,
           i->d1r,
           i->dl,
           i->d2r,
           i->rate_correction,
           i->rr,
           i->am
    );
}

int main(int argc, char *argv[]) {
    printf("Model 2 Music Extractor\n");
    if (!argv[1]) {
        printf("No file provided\n");
        return 1;
    }
    FILE *mpr;
    mpr = fopen(argv[1], "rb");

    Instrument *instr1 = make_instrument();
    printf(" id |   start  | loop  |  end  |lfo |vib | ar |d1r | dl |d2r | rc | rr |am\n");
    for (int i = 0; i < 215; i++) {
        read_instrument(i, mpr, instr1);
        printf("%3i | ", i);
        print_instrument(instr1);
        write_instrument(i, mpr, instr1);
    }
    fclose(mpr);
    return 0;
}