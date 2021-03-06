#include<c8051f310.h>   // include称为文件包含命令,扩展名为.h的文件称为头文件
unsigned int i,j,m;
/************************************************************
unsigned即C语言中的无符号变量说明符//在上面定义i,j,m的时候我们采用的是无符号整型，原因在于防止发生数据溢出现象，实//际上我们也可以用int型，只要保证我们用到的数在相应的数据范围以内即可。************************************************************/

/************************************************************
 //无论是本实验还是后续试验我们书写的程序都是由各个程序模块组成的，以本实验为例，它有四个大的//程序模块：1、系统时钟部分；2、I/O口部分（I即input：输入,O即output：输出）；3、延时程序部//分；4、主程序部分。在后续的实验中我们还会用到其他程序模块，如：定时器部分，中断部分，PWM部//分等。系统时钟的设置说明在手册的92～95页，在此我们简单说明一下，系统时钟提供给单片机所需要//的工作频率，正如我们电脑的主频一样。单片机的系统时钟是由振荡器提供的，振荡器分为外部振荡器和内部振荡器，内部振荡器又分为内部高频和内部低频，在此我们用到是内部高频振荡器。
************************************************************/
void sys(void)    //设置系统时钟 
 {
 CLKSEL=0X00;  //CLKSEL:时钟选择寄存器
/* 0X00中0X为十六进制的代表符号,0X00即为二进制下的0000 0000，设置该寄存器时由于位7～2我们//没有用到，因此便统一设置为0，而位1～0 设置为00的原因是我们所采用的系统时钟取自内部高频振//荡器； */
 OSCICL=0X2D;   //OSCICL:内部高频振荡器校准寄存器（请大家翻到数据手册的第93页），
/*0X2D翻译为二进制即（0010 1101）自左往右，分别对应P0.7～P0.0，下面我们来具体分析其设置过程，//位7（即P0.7）未用，所以该位设置为0，位6～0所对应的数转化为十进制数即45，该值是通过计算得//出的，计算过程请大家参考93页内容。通过该寄存器的设置我们便得到了20MHz的系统时钟。 */
 OSCICN=0XC2;//OSCICN:内部高频振荡器控制寄存器，
/*0XC2即1100 0010，位7置1，使能内部高频振荡器；位6置1，内部高频振荡器按编程频率运行；位5～2未用，置0；位1～0置为10，选择2分频，这样我们便得到了10MHz的系统时钟（在OSCICL中我们得到了20MHz，将其2分频即除以2）。*/
 }
 
void pio(void) /*设置I/O口（请大家查阅手册的98～111页）上面我们讲过P0与P1其基本功能是并列的，在本实验中我们任取其一，下面以P0为例说明*/
{
XBR0=0X00;//XBR0:端口I/O交叉开关寄存器0
/***位7位6未用，置0；位5位4对应的功能我们没有用到（也不常用），所以选择置0；位3置0或1对//本实验没有影响，但在此我们着重讲一下，该位为SYSCLK输出使能位，它的作用是当我们想用示波器测//量系统时钟频率时，我们需要将该位置1。具体来讲该位如同存在于系统时钟与端口引脚之间的桥梁，//置0时桥梁断开，不通行；置1时桥梁通行；系统时钟的工作频率输出给端口引脚，这时候我们只要再//将端口引脚连接到示波器，就可以显示出单片机的工作频率了。位2～0对应的功能不常用，置0。**/
XBR1=0XC0;// 端口I/O交叉开关寄存器1
/*位7:端口I/O弱上拉禁止位。弱上拉，最简单的讲法就是：比较弱的上拉。一般用在和外围器件的通讯上，但不能用于需要驱动能力的上拉应用中。弱上拉是在用作输入时省掉外部上拉,如果一个I/O口作输入,我们要求它在没有外部输入的情况下要为高电平,如按键输入,有按键按下时将其置地拉低,平时为高,这时如果不开内部上拉的话我们就要在外面加一个上拉电阻了。在本实验中我们没有用到该功能，所以置1。位6：交叉开关使能位，请大家翻到手册104页，我们可以看到数字交叉开关具有非常重要的作用，它是很多功能的总开关。如果我们已经已经设置好了所需的功能，但是交叉开关却没有使能，那么所需的功能仍然是无法实现的，所以在每次实验时我们要记得使能交叉开关。位5位4分别是定时器T1和T0，在本实验中我们没有用到，置0。在此我们简单介绍一下，定时器具有计数/定时功能，以位5为例，如果我们将其置1使T1连接到端口引脚，则T1可以对端口引脚进行计数，在实验二红外计数实验中我们将用到该功能，在此不做赘述。详细内容请大家查阅手册146页定时器部分。位3不常用到，置0；位2未用置0；位1～0：PCA模块I/O使能位，在后面的控制电机实验中需要使用到该部分，*/
P0MDIN=0XFF;//端口0输入方式寄存器
//端口引脚主要有两种输入方式：模拟输入和数字输入，模拟信号是连续的，如声波信号，温度信号；而数字信号指幅度的取值是离散的，幅值表示被限制在有限个数值之内。二进制码就是一种数字信号。在我们目前接触到的实验中，除温度计实验利用到模拟信号输入外，其余实验我们一律用数字信号输入。
P0MDOUT=0X10;// 端口0输出方式寄存器
/*推挽输出：可以输出高、低电平，连接数字器件；开漏输出输出端相当于三极管的集电极，要得到高电//平状态需要上拉电阻才行。 适合于做电流型的驱动，其吸收电流的能力相对强(一般20ma以内)。推挽//结构一般是指两个三极管分别受两互补信号的控制，总是在一个三极管导通的时候另一个截止，其开关//能力强。
漏极开路：它是驱动电路的输出三极管的集电极开路，可以通过外接的上拉电阻提高驱动能力，故其驱动能力强。在本实验中我们要驱动发光二极管发光，因此要求驱动能力强，因此采用漏极开路。*/
P0SKIP=0X0F;//端口0跳过寄存器
/*前面我们已经讲过使能交叉开关的作用，现在我们介绍一下其设置要求。当一个数字资源被选择时，尚未分配的端口引脚中的最低位被分配给该资源。如果一个端口引脚已经被分配，则交叉开关在为下一个被选择的资源分配引脚时将跳过该引脚。此外交叉开关还将跳过在PnSKIP寄存器中被置"1"的那些位对应的引脚。比如在本次试验中我们用P0.3～P0.0来控制发光二极管，那么如果我们还需要用到P0的其他脚口我们就要需要先跳过这四个已被使用的脚口。对于一些特殊功能的使用规则请大家参考100，101页的优先权译码表，看表时要记得按照"自上而下，自左往右"的顺序优先权依次降低。例如：如果我们同时用到CP0和CP0A功能，由图可知两者均可以使用P0.0引脚，但是由于CP0在CP0A之上，故优先权高于CP0A此时如果CP0使用了P0.0引脚，那么CP0A只能从P0.0右边的引脚中选择，如果忽视了优先权，CP0A选择了P0.0，那么根据优先权规则CP0便没有引脚可选了；再比如：如果我们只用到了特殊功能CP0A，那么按照优先权要求，如果P0.0没有被其他功能用到，此时CP0A会优先选择P0.0，但是如果P0.0已经被其他功能占用了或者我们不想使用P0.0引脚，那么我们就需要跳过（SKIP）P0.0，跳过之后按照优先权要求CP0A会选择P0.1，但是如果P0.1也已经被占用或者我们也不想使用P0.1，那么我们就需要再次跳过P0.1，依此类推。*/   
}

/***************************************************************************/
void delay(m) //延时程序
{
for(i=0;i<1000;i++)
for(j=0;j<m   ;j++)//如下所示m=500，每执行一次i++，j++就需要500次，那么当i=1000时，循环//次数=500*1000，再乘以工作周期T,便可以得出t=0.6s了。
{; ;}  //这是一个空语句，虽然没有实际意义，但在循环语句中它是经常用到的。
}

/****************延时程序顾名思义就是起延长时间的作用，下面我们以本程序为例来说明：由我们前面设置的系统时钟可知，单片机的工作频率为f=10MHz，那么根据周期与频率的倒数关系易知T=1/f=0.0000001秒，则一个机器周期为T*12=1.2us。因此单片机执行程序的速度是相当迅速的，在本实验中如果没有延时程序，其后果是我们根本看不到灯亮（人的眼睛一个重要特性是视觉惰性，即光象一旦在视网膜上形成，视觉将会对这个光象的感觉维持一个有限的时间，这种生理现象叫做视觉暂留性。对于中等亮度的光刺激，视觉暂留时间约为0．05至0．2s），因此我们要想看到二极管按照程序要求依次发光就需要让二极管在亮了以后继续维持一定的时间，这便是延时程序的作用了。以本实验设置的数据为例：每执行一次delay程序，延时时间t=1000*500*(0.0000012s)=0.6s，达到了视觉要求，当然我们在这里只是理论上的计算，实际上单片机的工作频率是存在较小偏差的，在做本实验时每个人可以根据实际情况来决定延时时间。（注意观察延时时间不同所带来的效果，这对理解后续试验"控制数码管发光""电子时钟"很有帮助。）*****************************/

/***************************************************************************/
main()//主程序
{
PCA0MD&=~0X4D;/*关闭看门狗 看门狗的作用就是防止程序发生死循环，或者说程序跑飞。但是在机器人比赛中，为了提高胜率，即使是程序跑飞，我们也要让它继续工作下去，所以我们要把"狗"关起来。*/
sys();//调用前面的系统时钟程序
pio();//调用前面的I/O口程序
while(1)//whlie(1)表示的是死循环，即程序循环执行下去。
{
P0=0x0E;delay(500);//00001110 P0.0对应的二极管发光
P0=0X0D;delay(500);//00001101 P0.1对应的二极管发光
P0=0X0B;delay(500);//00001011 P0.2对应的二极管发光
P0=0X07;delay(500);//00000111 P0.3对应的二极管发光
P0=0X00;delay(500);//00000000 四个二极管全部发光
P0=0X0F;delay(500);//00001111 四个二极管全部不发光
}
}
