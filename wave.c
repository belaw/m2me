//
// Created by Jonas on 20.12.2015.
//

#include "wave.h"

WaveHeader *make_WaveHeader(WORD channels, DWORD sampleRate, WORD bitsPerSample, unsigned short dataLength) {
    WaveHeader *h = malloc(sizeof(WaveHeader));
    h->chunkID = 0x46464952;
    h->format = 0x45564157;

    h->subChunk1ID = 0x20746D66;
    h->subChunk1Size = 16;
    h->audioFormat = 1;
    h->numChannels = channels;
    h->sampleRate = sampleRate;
    h->bitsPerSample = bitsPerSample;
    h->byteRate = h->sampleRate * h->numChannels * h->bitsPerSample / 8;
    h->blockAlign = (WORD) (h->numChannels * h->bitsPerSample / 8);

    h->subChunk2ID = 0x61746164;
    h->subChunk2Size = (DWORD) (dataLength * h->numChannels * h->bitsPerSample / 8);
    h->chunkSize = 4 + (8 + h->subChunk1Size) + (8 + h->subChunk2Size);

    return h;
}

WaveSmplChunk *make_WaveSmplChunk() {
    WaveSmplChunk *s = malloc(sizeof(WaveSmplChunk));
    s->chunkID = 0x6C706D73;
    s->chunkSize = sizeof(WaveSampleLoop) + (sizeof(DWORD) * 9);

    s->manufacturer = 0;
    s->product = 0;
    s->samplePeriod = 0;
    s->midiUnityNote = 0;
    s->midiPitchFraction = 0;
    s->smpteFormat = 0;
    s->smpteOffset = 0;
    s->numSampleLoops = 1;
    s->samplerData = 0;

    return s;
}

WaveSampleLoop *make_WaveSampleLoop(DWORD cuePointID, DWORD type, DWORD start, DWORD end, DWORD fraction,
                                    DWORD playCount) {
    WaveSampleLoop *l = malloc(sizeof(WaveSampleLoop));
    l->cuePointID = cuePointID;
    l->type = type;
    l->start = start;
    l->end = end;
    l->fraction = fraction;
    l->playCount = playCount;

    return l;
}

WaveXtraChunk *make_WaveXtraChunk() {
    WaveXtraChunk *e = malloc(sizeof(WaveXtraChunk));
    e->chunkId = 0x61727478;
    e->chunkSize = 16;

    e->unk1 = 0;
    e->unk2 = 0x80000001;
    e->unk3 = 0x40000000;
    e->unk4 = 0;

    return e;
}

WaveListChunk *make_WaveListChunk(DWORD chunkSize) {
    WaveListChunk *l = malloc(sizeof(WaveListChunk));
    l->chunkID = 0x5453494C;
    l->chunkSize = chunkSize;

    l->typeID = 0x4F464E49;

    return l;
}

WavePadding *make_WavePadding() {
    WavePadding *p = malloc(sizeof(WavePadding));
    p->padding = 0;

    return p;
}

WaveChunk *make_WaveChunk(DWORD chunkID, DWORD chunkSize) {
    WaveChunk *c = malloc(sizeof(WaveChunk));
    c->chunkID = chunkID;
    c->chunkSize = chunkSize;

    return c;
}