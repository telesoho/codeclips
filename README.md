# codeclips
Some useful code clips for my work.

# Recognize Sound

[ライフゲームの世界](http://aidiary.hatenablog.com/entry/20130105/1357353184)

[Recognizing Sounds (A Deep Learning Case Study)](https://medium.com/@awjuliani/recognizing-sounds-a-deep-learning-case-study-1bc37444d44d)

You can download data set from here [data set of Recognizing Sounds](https://medium.com/@awjuliani/hi-rajat-e0bf4b96dfeb).


https://github.com/ybayle/awesome-deep-learning-music


https://qiita.com/eve_yk/items/07bc094538f2d50841f4

```ocavle
WinLen = 1;
SamplingFrequence = 44100;
SamplingLen = SamplingFrequence * WinLen;
clear AudioData, SamplingFrequence;
[chord1, SamplingFrequence] = audioread("chord1.wav", [1, SamplingLen]);
[fret_3rd, SamplingFrequence] = audioread("3rd_fret.wav", [1, SamplingLen]);

SamplingPeriod = 1/SamplingFrequence;

% Time = (0:length(chord1)-1) * SamplingPeriod;

chord1FFT = fft(chord1);
fret_3rdFFT = fft(fret_3rd);

chord1P2 = abs(chord1FFT/SamplingLen);
chord1P1 = chord1P2(1:SamplingLen/2+1);
chord1P1(2:end-1) = 2*chord1P1(2:end-1);

fret_3rdP2 = abs(fret_3rdFFT/SamplingLen);
fret_3rdP1 = fret_3rdP2(1:SamplingLen/2+1);
fret_3rdP1(2:end-1) = 2*fret_3rdP1(2:end-1);

Frequence = (SamplingFrequence/SamplingLen)*(0:(SamplingLen/2));

figure (1);
plot(Frequence, chord1P1);
figure (2);
plot(Frequence, fret_3rdP1);


title('Single-Sided Amplitude Spectrum of X(t)');
xlabel('f (Hz)');
ylabel('|P1(f)|');
```
