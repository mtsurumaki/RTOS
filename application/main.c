#include "typedef.h"
#include "sysdef.h"
#include "syslib.h"

#define DATA_BIT 40 //データ数は40
#define STD_TIME 50 //データが0か1か判断する基準時間

/* 時間待ち関数 */
static void delay_ms( UINT ms)
{
    UINT cnt = ms/TIMER_PERIOD;

    while(cnt) {
        if((in_w(SYST_CSR) & SYST_CSR_COUNTFLAG)!=0) {  /* TIMER_PERIOD経過するとフラグがセット */
            cnt--;
        }
    }
}

void shiftOut(UB dataPin, UB clockPin, UB val)
{
	UB i;
    UW setWord;

    setWord = 0;
	for (i = 0; i < 8; i++) {
        setWord = (GPIO_OUT);
        out_w(GPIO_OUT, (setWord | ((val & 1)<<dataPin)));
        val >>= 1;
		out_w(GPIO_OUT, (setWord | (1<<clockPin)));
		out_w(GPIO_OUT, (setWord | (0<<clockPin)));
	}
}

// int main(void) {
//     UW j;
//     UW setWord;
//     UB dataPin;
//     UB clockPin;
//     const UB puttrns[8] = {
//         0b10000000,
//         0b01000000,
//         0b00100000,
//         0b00010000,
//         0b00001000,
//         0b00000100,
//         0b00000010,
//         0b00000001
//     };

//     /* 初期化 */
//     setWord = 0;
//     out_w(GPIO_OUT, setWord);
//     dataPin = 5;
//     clockPin = 6;

//     /* メインループ */
//     while (TRUE) {
//         for(i=0;i<8;i++){
//             out_w(GPIO_OUT_XOR, latchPin);
//             shiftOut(dataPin, clockPin, puttrns[i]);
//             out_w(GPIO_OUT_XOR, latchPin);
//             delay_ms(2000);
//         }
//     }
// }

int main(void) {
    UW setWord;

    /* 初期化 */
    setWord = 0;
    out_w(GPIO_OUT, setWord);

    /* メインループ */
    while (TRUE) {
        out_w(GPIO_OUT, 1<<25);
        delay_ms(2000);
        out_w(GPIO_OUT, 1<<24);
        delay_ms(2000);
        out_w(GPIO_OUT, setWord);
        delay_ms(2000);
    }
}
