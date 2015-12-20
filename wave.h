//
// Created by Jonas on 20.12.2015.
//

#ifndef M2ME_WAVE_H
#define M2ME_WAVE_H

#include <minwindef.h>

//typedef enum {LOOP_NORMAL,LOOP_ALTERNATING,LOOP_BACKWARD} waveSampleLoopType;

typedef struct {
    DWORD chunkID;       // 0x52494646 "RIFF" in big endian
    DWORD chunkSize;     // 4 + (8 + subChunk1Size) + (8 + subChunk2Size)
    DWORD format;        // 0x57415645 "WAVE" in big endian

    DWORD subChunk1ID;   // 0x666d7420 "fmt " in big endian
    DWORD subChunk1Size; // 16 for PCM
    WORD audioFormat;   // 1 for PCM
    WORD numChannels;   // 1 for mono, 2 for stereo
    DWORD sampleRate;    // 8000, 22050, 44100, etc...
    DWORD byteRate;      // sampleRate * numChannels * bitsPerSample/8
    WORD blockAlign;    // numChannels * bitsPerSample/8
    WORD bitsPerSample; // number of bits (8 for 8 bits, etc...)

    DWORD subChunk2ID;   // 0x64617461 "data" in big endian
    DWORD subChunk2Size; // numSamples * numChannels * bitsPerSample/8 (this is the actual data size in bytes)
} WaveHeader;

WaveHeader *make_WaveHeader(WORD channels, DWORD sampleRate, WORD bitsPerSample, unsigned short dataLength);

typedef struct {
    DWORD chunkID;    // Chunk ID  "smpl" (0x736D706C)
    DWORD chunkSize;    // Chunk Data Size 36 + (Num Sample Loops * 24) + Sampler Data

    DWORD manufacturer;    // Manufacturer  0 - 0xFFFFFFFF
    DWORD product;    // Product 0 - 0xFFFFFFFF
    DWORD samplePeriod;    // Sample Period 0 - 0xFFFFFFFF
    DWORD midiUnityNote;    // MIDI Unity Note 0 - 127
    DWORD midiPitchFraction;    // MIDI Pitch Fraction 0 - 0xFFFFFFFF
    DWORD smpteFormat;    // SMPTE Format  0, 24, 25, 29, 30
    DWORD smpteOffset;    // SMPTE Offset  0 - 0xFFFFFFFF
    DWORD numSampleLoops;    // Num Sample Loops  0 - 0xFFFFFFFF
    DWORD samplerData;    // Sampler Data  0 - 0xFFFFFFFF
} WaveSmplChunk;

WaveSmplChunk *make_WaveSmplChunk();

typedef struct {
    DWORD cuePointID;
    DWORD type;
    DWORD start;
    DWORD end;
    DWORD fraction;
    DWORD playCount;
} WaveSampleLoop;

WaveSampleLoop *make_WaveSampleLoop(DWORD cuePointID, DWORD type, DWORD start, DWORD end, DWORD fraction,
                                    DWORD playCount);

typedef struct {
    char padding;
} WavePadding;

WavePadding *make_WavePadding();

typedef struct {
    DWORD chunkId;
    DWORD chunkSize;
    int unk1;
    int unk2;
    int unk3;
    int unk4;
} WaveXtraChunk;

WaveXtraChunk *make_WaveXtraChunk();

typedef struct {
    DWORD chunkID;
    DWORD chunkSize;
    DWORD typeID;
} WaveListChunk;

WaveListChunk *make_WaveListChunk(DWORD chunkSize);

typedef struct {
    DWORD chunkID;
    DWORD chunkSize;
} WaveChunk;

WaveChunk *make_WaveChunk(DWORD chunkID, DWORD chunkSize);

#endif //M2ME_WAVE_H
