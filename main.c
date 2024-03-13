#include <Windows.h>
#include <stdio.h>

#define VOLUME 0xFFFF

BYTE sbuffer[184060 * 60];
DWORD nSamples = 44000;

void PlayFrom(DWORD offset)
{
    for (int t = 0; t < sizeof(sbuffer); t++)
    {
        sbuffer[t] = sbuffer[offset];

        offset++;

        if (offset > sizeof(sbuffer))
        {
            return;
        }
    }
}

int main(int argc, char* argv[])
{
    //Put the dir of your PCM Audio here
    FILE* f = fopen("Samples/BadApple.pcm", "rb");

    if (!f)
    {
        printf("[-] Couldn't find the file!");
        return -1;
    }

    fread(sbuffer, sizeof(BYTE), sizeof(sbuffer), f);
    fclose(f);

    //PlayFrom(1000 * 1000);

    HWAVEOUT hWaveOut = { 0 };

    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, nSamples, nSamples, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    WAVEHDR header = { (LPSTR)sbuffer, sizeof(sbuffer), 0, 0, 0, 0, 0, 0 };

    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	
    waveOutSetVolume(hWaveOut, MAKELONG(VOLUME, VOLUME));
	
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);

    Sleep(8000 * 1000);

    return 0;
}
