ffmpeg\ffmpeg.exe -framerate 24 -i %04d.png jello_output.mp4

ffmpeg -i %04d.png -vf "zoompan=d=24+'124'*eq(in,1)" jello_3diffKs2.mp4

ffmpeg\ffmpeg -i video.mp4 -i image2.png -filter_complex "[0:v][1:v] overlay=25:25:enable='between(t,0,4)'" -pix_fmt yuv420p -c:a copy output3.mp4

ffmpeg\ffmpeg -i "concat:doable1.mp4|doable2.mp4|doable3.mp4|doable4.mp4" -c copy final_output.mp4

ffmpeg\ffmpeg -f concat -i names.txt -codec copy final_output.mp4