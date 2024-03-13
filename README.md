# PCM-Player
Windows audio player using PCM audio and WaveOut
# Compiling
### PCM Audio
`ffmpeg -i BadApple.mp3 -f u8 -acodec pcm_u8 -ar 22000 -ac 2 BadApple.pcm` <br />
`ffmpeg -i NightOfNights.mp3 -f u8 -acodec pcm_u8 -ar 22000 -ac 2 NightOfNights.pcm`

### C File
`gcc main.c -o main.exe -lwinmm`
