// sineosc.cpp STK tutorial program

#include "FileLoop.h"
#include "FileWvOut.h"
#include <cstdlib>

using namespace stk;

int main()
{
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 44100.0 );

  int nFrames = 100000;
  FileLoop input;
  FileWvOut output;

  try {
    // Load the sine wave file.
    input.openFile( "rawwaves/sinewave.raw", true );

    // Open a 16-bit, one-channel WAV formatted output file
    output.openFile( "hellosine.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16 );
  }
  catch ( StkError & ) {
    exit( 1 );
  }

  
    // 计算规则
    //     100000/44100 = 2.27
    //     setFrequency 441(每秒次数)
    //         44频率变低,一个frames
    //         4400频率变高
    //             是什么啊？resample吗？
    //         是的，input是44个frames,对应的output调用的是100000次，每秒44100次，所以，对应的是input的44 * frames，所以设置 input的frequecy决定，正弦函数的波动次数
    //
    //             input frames
    input.setFrequency( 44.0 );

  // Option 1: Use StkFrames
  /*
  StkFrames frames( nFrames, 1 );
  try {
    output.tick( input.tick( frames ) );
  }
  catch ( StkError & ) {
    exit( 1 );
  }
  */

  // Option 2: Single-sample computations
  for ( int i=0; i<nFrames; i++ ) {
    printf("\ntry version 1.3 \n");
    try {
      output.tick( input.tick() );
        // 有符号位16bit
    }
    catch ( StkError & ) {
      exit( 1 );
    }
  }

  return 0;
}
