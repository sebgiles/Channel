
#ifndef CHANNEL_CPP
#define CHANNEL_CPP

#include "Channel.h"

template <typename P>
void Channel<P>::init(HardwareSerial& s, long baud, char ID, void(*cb)(P&)){
  id=ID;
  Serial=&s;
  callback=cb;
  Serial->begin(baud);
}

template <typename P>
void Channel<P>::check(){
  if (Serial->peek()==id){
    Serial->read(); //discard id byte
    P p;
    Serial->readBytes((char*)&p, sizeof(P));
    callback(p);
  }
}

template <typename P>
void Channel<P>::send(const P &p){
  Serial->write(id);
  Serial->write((char*)&p,sizeof(P));
}

#endif
