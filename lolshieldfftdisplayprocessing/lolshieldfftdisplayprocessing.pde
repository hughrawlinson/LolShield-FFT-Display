import processing.serial.*;

import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

Minim minim;
AudioInput in;
FFT fft;
Serial myPort;

void setup(){
  size(640,480);
  minim = new Minim(this);
  in = minim.getLineIn(Minim.STEREO,512);
  fft = new FFT(in.bufferSize(), in.sampleRate());
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[6], 9600);
  
  stroke(255);
}

void draw(){
  background(0);
  fft.forward(in.mix);
  for(int i = 0; i < fft.specSize(); i+= fft.specSize()/18){
    line(i/14*fft.specSize()/14, height, i/14*fft.specSize()/14, height - fft.getBand(i) * 4);
    // String send = (int)(map(fft.getBand(i),0,35,0,9)) + " " + i/14 + "\n";
    String send = 0 + " " + i/14 + "\n";
    if(i/14<14){
      myPort.write(send);
      print(send);
    }
  }
}
