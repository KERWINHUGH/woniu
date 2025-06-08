/***************************************************
# File Name:    18-20250224-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:03:44 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

// 1 * 9 = 9	1 * 9 = 9 ....   （9个）
// 把列数改成动态的
// 输出9行上面的代码。
// 再把行数也改成动态的。
// 通过行数，控制列数 （乘法口诀表）
void one(){
	// 外层循环控制行数
	for(int j = 1; j <= 9; j++ ){
	
		// 里层的循环，控制列数
		for(int i = 1; i <= j; i++){
			printf("%d * %d = %d \t", i , j , i * j );
		}
		printf("\n");
	}
}
// 组合问题: 用一元兑换1分、2分、5分的硬币，兑换数量为50枚，问可以有多少种组合的方式
void two(){
	int n = 0;
	int count = 0;
	// 枚举所有的可能 1分，2分，5分的硬币组合
	for(int one = 0; one <= 50; one++){
		for(int two = 0; two <= 50; two++){
			n++;
			int five = 50 - one - two;
			// 检查总金额数
			if(five >= 0 && one + 2 * two + 5* five == 100){
				count++;
				printf("1分：%d, 2分：%d, 5分：%d \n", one, two, five);
			}
		}
	}
	
	/*
	for(int one = 0; one <= 50; one++){
		for(int two = 0; two <= 50; two++){
			for(int five = 0; five<=50; five++){
				n++;
				if( one + 2 * two + 5* five == 100 && one + two + five == 50){
					count++;
					printf("1分：%d, 2分：%d, 5分：%d \n", one, two, five);
				}
			}
		}
	}
	*/
	
	printf("一共有%d个组合.循环了：%d 次。\n", count, n );

}

// 抓球问题：有红球5个，黑球7个、白球9个。随机取出12个，求所有的取球方式并输出方式数量:for嵌套
void three(){
	int count=0;
	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 7; j++){
			for(int k = 0; k <= 9; k++ ){
				if(i + j + k == 12){
					printf("red:%d, black:%d, white:%d \n", i, j, k);
					count++;
				}
			}
		}
	}

	printf("一共有：%d 个方式.\n ", count);
}

// 有一天焜哥在卖鸡，每到一个地方卖出一半又多1只，第6个地方卖了之后，手上只有1只了，问最开始有几只鸡。
void four(){
	int chinckens = 1;
	
	for(int i = 0 ; i < 6; i++){
		chinckens = (chinckens + 1)*2;
	}
	printf("原来有：%d 只鸡 \n", chinckens);	
}



int main(int argc, char *argv[]) {
	
	four();

    return 0;
}

























