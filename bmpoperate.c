//바이너리 형식으로 보존된 Windows Bitmap 형식의 화상 파일을 읽어, 3개의 색성분 (R, G, B)로 분리해,
//각각의 다른 파일 (각 blue.bmp, green.bmp, red.bmp)로 보존하는 프로그램을 만들어라. 프로그램 중에 하는 것은 이하.
//1.헤더 부분을 적절히 읽기
//2.읽은 헤더 부분 (파일 헤더, 정보 헤더)를 이용해서, 적절한 바이트 수 (화소수 * 1화소수 당 바이트 수)를 읽어 온다.
//이게 InputImg[400][300][3] 화소수는 300 * 400 1화소수 당 바이트 수는 3 즉 300*400*3
//3.분리하고 싶은 색성분 이외를 0으로 바꿔 써, 헤더 부분과 색정보를 파일에 써 넣는다

//발전과제
//예로, 읽은 화상의 컬러의 변환, 화상의 반전, 회전 등을 생각한다.
//범용성을 가진 프로그램으로 확장하기 위해서는, 가로세로의 사이즈가 다른 경우에도 대응가능하도록,
//화상의 헤더 부분을 조작할 필요가 있다. 또, 가로 한 줄의 길이(픽셀 수)가 4의 배수가 되어있지 않은 경우에는,
//줄을 나타내기 위한 바이트 수를 조정할 필요가 있다. (가로 라인을 4바이트로 나누어 떨어지는 바이트 수로 써넣지 않으면 안 된다)
//조정을 행하는 경우에는, 적당한 값(예를 들면 0)을 쓰면 된다.


//이번 화상 파일은 한 화소 당 24bit(3 byte)의 정보를 가진다.
//각 화소는 Blue(8 bit), Green (8 bit), Red (8 bit)의 순으로 색의 값이 기록되어있다.
//일반적으로, 화상 데이터는 좌측 하단에서부터 우측 상단으로 향해서 기록되어있다.

//화상 옆 라인의(1행)의 데이터의 길이는. 4byte의 경계의 정돈되어 있어야 한다.(횡 라인을 4바이트로 나눌 수 있는 수로 써 넣어야 함)
//그러나, 이번 회차는 세로 300화소, 가로 400화소(횡 라인 1행 전부로 400*3 = 1200byte)이다. 따라서 신경쓰지 않아도 된다

//각 색당 8bit(1byte), 합계 24bit(3byte)로 보존된다.
//1화소당 24bit(3byte), blue(8bit = 1byte), green(8bit), red(8bit) 순
//각 색 다 char형의 변수(1Byte)로 보존하는 것이 가능하다.

//파일 선두에서 14Byte는 파일 헤더, 파일 헤더에서부터 40Byte는 정보헤더
//정보헤더의 뒤부터는, 각 화소의 B성분, G성분, R성분이 화상의 좌측 하단에서부터 매 행마다 보존되어있다. (물론 바이너리로)

#include <stdio.h>

typedef struct { //파일 헤더
	unsigned short	bfType; //파일 타입 0x42, 0x4d
	unsigned int	bfSize; //파일 사이즈 byte
	unsigned short	bfReserved1; //예약 영역 (항상 0)
	unsigned short	bfReserved2; //예약 영역 (항상 0)
	unsigned int	bfOffBits; //화상 데이터 까지의 오프셋 (오프셋: 파일의 선두로부터의 바이트 수)
} BitmapFileHeader;

typedef struct { //정보 헤더
	unsigned int	biSize; //정보 헤더의 사이즈 (12 or 40)
	int				biWidth; //화상의 폭 pixel
	int				biHeight; //화상의 높이 pixel
	unsigned short	biPlanes; //플레인 수 (언제나 1)
	unsigned short	biBitCount; //한 화소당 색 수 bit (이번 화상은 24)
	unsigned int	biCompression; //압축형식 0 or 1 or 2 or 3 (이번 화상은 0)
	unsigned int	biSizeImage; //화상 데이터의 사이즈 byte
	int				biXPixPerMeter; //수평해상도 ppm
	int				biYPixPerMeter; //수직해상도 ppm
	unsigned int	biClrUsed; //팔레트 색상 수
	unsigned int	biClrImportant; //중요한 팔레트의 인덱스
} BitmapInfoHeader;

typedef struct { //여기를 생각해야 함
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
} RGBtriple;

RGBtriple hRGB[256];//✔✔
unsigned char InputImg[400][300][3];
unsigned char OutputImg[400][300][3];

//복기
//헤더 파일 뒤에 RGB바이너리 데이터가 있다는 것을 인식하면, char형의 Blue, Red, Green으로 이루어진
//RGB구조체를 만들어서 구조체 배열(hRGB[256])을 선언했어야 했다.
//또 InputImg와 OutputImg를 선언하여, [400][300][3]의 구조체에서, 400은 너비, 300은 높이, 3은 각 RGB데이터의 개수인것을 이용
//각각의 char형 Blue, Red, Green데이터가 sizeof(char) = 1Byte 이라는 것을 생각했어야 함


int main(void)
{
	FILE *fp, *fq;
	FILE *fb, *fg, *fr; //blue.bmp, red.bmp, green.bmp로 보존하는 메인스트림
	FILE *frv; //반전
	
	BitmapFileHeader fileh; //BitmapFileHeader의 형식(파일 헤더)을 가진 fileh 를 선언
	BitmapInfoHeader filel; //BitmapInfoHeader의 구조(정보 헤더)를 가진 filel 을 선언
	
	fp = fopen("bmpsample.bmp", "rb"); //fp는 bmpsample.bmp에서 읽는다
	fq = fopen("bmpsample.data", "wb"); //fq는 bmpsample.data에 쓴다 (바이너리 파일로)
	fb = fopen("blue.bmp", "wb");
	fr = fopen("red.bmp", "wb");
	fg = fopen("green.bmp", "wb");
	frv = fopen("reversal.bmp", "wb");
	
	/*
 	fread(&(fileh.bfType), 2, 1, fp);
	//fread(포인터, 사이즈, 개수, 파일 포인터) 파일 포인터가(fp)가 가리키는 파일의 장소(bmpsample.bmp)로부터
	//사이즈 바이트(2)를 개수(1)만큼 읽어와 "포인터" (&(fileh.bfType)) 가 가리키는 주소에 써넣음
	fread(&(fileh.bfSize), 4, 1, fp); //사이즈 바이트: 4(sizeof int = 4) , 개수: 1
	fread(&(fileh.bfReserved1), 2, 1, fp); //sizeof(unsigned short) = 2
	fread(&(fileh.bfReserved2), 2, 1, fp);
	fread(&(fileh.bfOffBits), 4, 1, fp);
	
	fread(&(filel.biSize), 4, 1, fp);
	fread(&(filel.biWidth), 4, 1, fp);
	fread(&(filel.biHeight), 4, 1, fp);
	fread(&(filel.biPlanes), 2, 1, fp);
	fread(&(filel.biBitCount), 2, 1, fp);
	fread(&(filel.biCompression), 4, 1, fp);
	fread(&(filel.biSizeImage), 4, 1, fp);
	fread(&(filel.biXPixPerMeter), 4, 1, fp);
	fread(&(filel.biYPixPerMeter), 4, 1, fp);
	fread(&(filel.biClrUsed), 4, 1, fp);
	fread(&(filel.biClrImportant), 4, 1, fp);*/
	
	fread(&fileh, sizeof(BitmapFileHeader), 1, fp); //이걸로도 파일 읽기 쓰기 가능 (읽기 쓰기 둘다 이걸로 할때만)
	fread(&filel, sizeof(BitmapInfoHeader), 1, fp);
	//여기까지가 헤더 파일 읽는 메인스트림
	//파일 읽기 쓰기 처리를 구조체로 할 때, 구조체의 성분 하나하나 일일이 할 필요 없이
	//구조체 째로 파일을 읽어올 수 있단 것을 깨달음. (다만 읽기 쓰기 모두 똑같이 구조체 째로 해야됌!)
	
	fread(&hRGB, sizeof(RGBtriple), 256, fp); //✔
	fread(InputImg, 300*400*3, 1, fp); //✔ 
	//2.읽은 헤더 부분 (파일 헤더, 정보 헤더)를 이용해서, 
	//적절한 바이트 수 (화소수 * 1화소수 당 바이트 수)를 읽어 온다.
	
	for(int i =0; i < 400; i++){ //✔
		for(int j = 0; j < 300; j++){
			for(int k = 0; k < 3; k++){
				OutputImg[i][j][k] = InputImg[i][j][k];
			}
		}
	}
	
	
	/*
	fprintf(fq, "%d fileh.bfType\n", fileh.bfType);
	fprintf(fq, "%d fileh.bfSize\n", fileh.bfSize);
	fprintf(fq, "%d\n", fileh.bfReserved1);
	fprintf(fq, "%d fileh.bfOffBits\n", fileh.bfOffBits);
	
	fprintf(fq, "%d filel.biSize\n", filel.biSize);
	fprintf(fq, "%d filel.biWidth\n", filel.biWidth);
	fprintf(fq, "%d filel.biHeight\n", filel.biHeight);
	fprintf(fq, "%d filel.biPlanes\n", filel.biPlanes);
	fprintf(fq, "%d filel.biBitCount\n", filel.biBitCount);
	fprintf(fq, "%d filel.biCompression\n", filel.biCompression);
	fprintf(fq, "%d filel.biSizeImage\n", filel.biSizeImage);
	fprintf(fq, "%d filel.biXPixPerMeter\n", filel.biXPixPerMeter);
	fprintf(fq, "%d filel.biYPixPerMeter\n", filel.biYPixPerMeter);
	fprintf(fq, "%d filel.biClrUsed\n", filel.biClrUsed);
	fprintf(fq, "%d filel.biClrImportant\n", filel.biClrImportant);
	*/

	/*
	fwrite(&(fileh.bfType), 2, 1,fq);
	//fwrite(포인터, 사이즈, 개수, 파일 포인터) "포인터"가 가리키는 주소(&(fileh.bfType)로부터, 
	//"사이즈"바이트를 "개수"개를 "파일 포인터"가 가리키는 파일(fq)에 써 넣는다.
	fwrite(&(fileh.bfSize), 4, 1, fq);
	fwrite(&(fileh.bfReserved1), 2, 1, fq);
	fwrite(&(fileh.bfReserved2), 2, 1, fq);
	fwrite(&(fileh.bfOffBits), 4, 1, fq);
	
	fwrite(&(filel.biSize), 4, 1, fq);
	fwrite(&(filel.biWidth), 4, 1, fq);
	fwrite(&(filel.biHeight), 4, 1, fq);
	fwrite(&(filel.biPlanes), 2, 1, fq);
	fwrite(&(filel.biBitCount), 2, 1, fq);
	fwrite(&(filel.biCompression), 4, 1, fq);
	fwrite(&(filel.biSizeImage), 4, 1, fq);
	fwrite(&(filel.biXPixPerMeter), 4, 1, fq);
	fwrite(&(filel.biYPixPerMeter), 4, 1, fq);
	fwrite(&(filel.biClrUsed), 4, 1, fq);
	fwrite(&(filel.biClrImportant), 4, 1, fq);*/
	
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, fq); //이걸로도 파일 쓰기 가능 (읽기 쓰기 둘다 한꺼번에 할때)
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, fq);
	//여기까지가 헤더 파일 쓰는 메인스트림
	
	fwrite(&hRGB, sizeof(RGBtriple), 256, fq);//✔
	fwrite(OutputImg, 300*400*3, 1, fq);//✔
	
	
	for(int i = 0; i < 400; i++){ //가로의 길이:400 그러나 이걸 조정하면 가로가 아니라 전체의 세로가 수정됌
		for(int j = 0; j < 300; j++){ //각 가로줄의 세로 길이를 조정함
			for(int k = 0; k < 3; k++){
				if(k != 0){
					OutputImg[i][j][k] = 0; //k가 0일때만 남기면 Red
				}
			}
		}
	}
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, fr);
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, fr);
	fwrite(&hRGB, sizeof(RGBtriple), 256, fr);
	fwrite(OutputImg, 300*400*3, 1, fr);
	//RED
	
	
	for(int i = 0; i < 400; i++){ //가로의 길이:400 그러나 이걸 조정하면 가로가 아니라 전체의 세로가 수정됌
		for(int j = 0; j < 300; j++){ //각 가로줄의 세로 길이를 조정함
			for(int k = 0; k < 3; k++){
				if(k != 1){
					OutputImg[i][j][k] = 0; //k가 1일때만 남기면 BLUE
				}else{
					OutputImg[i][j][k] = InputImg[i][j][k]; //k가 1일때는 InputImg와 똑같이
				}
			}
		}
	}
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, fb);
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, fb);
	fwrite(&hRGB, sizeof(RGBtriple), 256, fb);
	fwrite(OutputImg, 300*400*3, 1, fb);
	//BLUE
	
	
	for(int i = 0; i < 400; i++){ //가로의 길이:400 그러나 이걸 조정하면 가로가 아니라 전체의 세로가 수정됌
		for(int j = 0; j < 300; j++){ //각 가로줄의 세로 길이를 조정함
			for(int k = 0; k < 3; k++){
				if(k != 2){
					OutputImg[i][j][k] = 0; //k가 2일때만 남기면 GREEN
				}else{
					OutputImg[i][j][k] = InputImg[i][j][k]; //k가 2일때는 InputImg와 똑같이
				}
			}
		}
	}
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, fg);
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, fg);
	fwrite(&hRGB, sizeof(RGBtriple), 256, fg);
	fwrite(OutputImg, 300*400*3, 1, fg);
	//GREEN
	
	
	//이것으로 깨달은 점: k = 0 이면 RED, k =1 이면 BLUE, k = 2이면 GREEN이다
	//RED, BLUE, GREEN 순으로 InputImg는 이루어져 있다.
	
	for(int i =0; i < 400; i++){ //✔
		for(int j = 0; j < 300; j++){
			for(int k = 0; k < 3; k++){
				OutputImg[i][j][k] = (InputImg[i][j][0]+InputImg[i][j][1]+InputImg[i][j][2])/3;
			}
		}
	}
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, frv);
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, frv);
	fwrite(&hRGB, sizeof(RGBtriple), 256, frv);
	fwrite(OutputImg, 300*400*3, 1, frv);
	//색 변경: Red -> Blue / Blue -> Green / Green -> Red
	//색 반전: OutputImg[i][j][k] = 255 - InputImg[i][j][k];
	//회전 : OutputImg[i][j][k] = InputImg[400-i][300-j][k];
	//흑백 : OutputImg[i][j][k] = (InputImg[i][j][0]+InputImg[i][j][1]+InputImg[i][j][2])/3
	//InputImg와 OutputImg는 unsigned char형이지만, 255에서 빼거나 다 합쳐서 평균값을 구하는 등의
	//수학적 계산으로 여러 편집을 할 수 있다.
	
	unsigned char NewOutputImg[800][300][3];
	
	for(int i = 0; i < 400; i++){
		for(int j = 0; j < 600; j++){
			for(int k = 0; k < 3; k++){
				NewOutputImg[2*i][j][k] = InputImg[i][j][k];
				NewOutputImg[i][2*j][k] = InputImg[i][j][k];
				NewOutputImg[2*i-1][j][k] = 0;
				NewOutputImg[i][2*j-1][k] = 0;
			}
		}
	}
	fwrite(&fileh, sizeof(BitmapFileHeader), 1, frv);
	fwrite(&fileh.bfSize, 800*600*3, 1, frv);
	fwrite(&filel, sizeof(BitmapInfoHeader), 1, frv);
	fwrite(&hRGB, sizeof(RGBtriple), 256, frv);
	fwrite(NewOutputImg, 800*600*3, 1, frv);
	
	
	
	return 0;
}