#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    //getting the acceptable number.
    long long n;
    do
    {
        n = get_long_long("Number: ");
    }
    while (n < 0 || n == 0);
    long long N = n;     //<<cheak later if it is correct.
    long long NN = N;

    //Counting number of digit in numbers.
    int digit;
    digit = 0;

    while (n > 0)
    {
        digit++;
        n /= 10;
    }

//1.Recognise the number in the front of card.
//2.Identify or invalidate the company of cards(Amex/MasterCard/Visa) by its number of digits.
//3.
    if (digit != 13 && digit != 15 && digit != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    long long DigitBy2S1,DigitBy2S2,DigitBy2S3,DigitBy2S4,DigitBy2S5,DigitBy2S6,TotalSum1,Sum1,Power1,Power2;
    long long digitBy2S1,digitBy2S2,digitBy2S3,digitBy2S4,TotalSum2,power1,power2;
    long long UltimateSum;
    int Index;
    int index;
//For AMEX(15 digits):
    //find the front number.
    if (digit == 15)
    {
        for (int i = 0; i < 15-2; i++)
        {
            N /= 10;
        }

        if (N == 34 || N == 37)
        {


            Index = 16;
            TotalSum1 = 0;
            for (int u = 0; u < 7; u++)
            {
                Index -= 2;
                Power1 = pow(10,Index);

                Power2 = pow(10,(Index - 1));


                DigitBy2S1 = NN / Power1;             //find the one of the important value for removing the right part

                DigitBy2S2 = DigitBy2S1 * Power1;    //remove the right part
                DigitBy2S3 = NN - DigitBy2S2;         //remove the left part
                DigitBy2S4 = DigitBy2S3 / Power2;    //find the digit number
                DigitBy2S5 = DigitBy2S4 * 2;         //double the digit found before.
                if (DigitBy2S5 >= 10)                //When number>=10,like 14,break it down into 1 and 4
                {
                    DigitBy2S6 = DigitBy2S5 - 10;
                    Sum1 = 1 + DigitBy2S6;
                    TotalSum1 = TotalSum1 + Sum1;
                }
                if (DigitBy2S5 < 10)                 //When number <10,add it into the sum.
                {
                    TotalSum1 = TotalSum1 + DigitBy2S5;
                }

            }



            index = 17;
            TotalSum2 = 0;
            for (int g = 0; g < 8; g++)              //for the rest of digit that do not need to double.
            {
                index -= 2;
                power1 = pow(10,index);
                power2 = pow(10,(index - 1));

                digitBy2S1 = NN / power1;             //find the one of the important value for removing the right part
                digitBy2S2 = digitBy2S1 * power1;    //remove the right part
                digitBy2S3 = NN - digitBy2S2;         //remove the left part
                digitBy2S4 = digitBy2S3 / power2;    //find the digit number,which is digitBy2S4
                TotalSum2 = TotalSum2 + digitBy2S4;
            }
            UltimateSum = TotalSum1 + TotalSum2;
            if(UltimateSum % 10 == 0)
            {
                printf("AMEX\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }

    }


//For MASTERCARD(16 digits):
    //find the front number.

    if (digit == 16)
    {
        for (int j = 0; j < 16-2; j++)
        {
            N /= 10;

        }
        if (N == 51 || N == 52 || N == 53 || N == 54 || N == 55)
        {
            //removed declaration of variables.
            Index = 18;
            TotalSum1 = 0;
            for (int u = 0; u < 8; u++)
            {
                Index -= 2;
                Power1 = pow(10,Index);
                Power2 = pow(10,(Index - 1));

                DigitBy2S1 = NN / Power1;             //find the one of the important value for removing the right part
                DigitBy2S2 = DigitBy2S1 * Power1;    //remove the right part
                DigitBy2S3 = NN - DigitBy2S2;         //remove the left part
                DigitBy2S4 = DigitBy2S3 / Power2;    //find the digit number
                DigitBy2S5 = DigitBy2S4 * 2;         //double the digit found before.
                if (DigitBy2S5 >= 10)                //When number>=10,like 14,break it down into 1 and 4
                {
                    DigitBy2S6 = DigitBy2S5 - 10;
                    Sum1 = 1 + DigitBy2S6;
                    TotalSum1 = TotalSum1 + Sum1;
                }
                if (DigitBy2S5 < 10)                 //When number <10,add it into the sum.
                {
                    TotalSum1 = TotalSum1 + DigitBy2S5;
                }

            }


            index = 17;
            TotalSum2 = 0;
            for (int g = 0; g < 8; g++)              //for the rest of digit that do not need to double.
            {
                index -= 2;
                power1 = pow(10,index);
                power2 = pow(10,(index - 1));

                digitBy2S1 = NN / power1;             //find the one of the important value for removing the right part
                digitBy2S2 = digitBy2S1 * power1;    //remove the right part
                digitBy2S3 = NN - digitBy2S2;         //remove the left part
                digitBy2S4 = digitBy2S3 / power2;    //find the digit number,which is digitBy2S4
                TotalSum2 = TotalSum2 + digitBy2S4;
            }

            UltimateSum = TotalSum1 + TotalSum2;
            if(UltimateSum % 10 == 0)
            {
                printf("MASTERCARD\n");
                return 0;
            }
        }
//if it is not mastercard, turn into checking if it is a VISA 16 digit card.
        else
        {
            N = N / 10;

            if (N == 4)
            {
                Index = 18;
                TotalSum1 = 0;
                for (int u = 0; u < 8; u++)
                {
                    Index -= 2;
                    Power1 = pow(10,Index);
                    Power2 = pow(10,(Index - 1));

                    DigitBy2S1 = NN / Power1;             //find the one of the important value for removing the right part
                    DigitBy2S2 = DigitBy2S1 * Power1;    //remove the right part
                    DigitBy2S3 = NN - DigitBy2S2;         //remove the left part
                    DigitBy2S4 = DigitBy2S3 / Power2;    //find the digit number
                    DigitBy2S5 = DigitBy2S4 * 2;         //double the digit found before.
                    if (DigitBy2S5 >= 10)                //When number>=10,like 14,break it down into 1 and 4
                    {
                        DigitBy2S6 = DigitBy2S5 - 10;
                        Sum1 = 1 + DigitBy2S6;
                        TotalSum1 = TotalSum1 + Sum1;
                    }
                    if (DigitBy2S5 < 10)                 //When number <10,add it into the sum.
                    {
                        TotalSum1 = TotalSum1 + DigitBy2S5;
                    }
                }

                index = 17;
                TotalSum2 = 0;
                for (int g = 0; g < 8; g++)              //for the rest of digit that do not need to double.
                {
                    index -= 2;
                    power1 = pow(10,index);
                    power2 = pow(10,(index - 1));

                    digitBy2S1 = NN / power1;             //find the one of the important value for removing the right part
                    digitBy2S2 = digitBy2S1 * power1;    //remove the right part
                    digitBy2S3 = NN - digitBy2S2;         //remove the left part
                    digitBy2S4 = digitBy2S3 / power2;    //find the digit number,which is digitBy2S4
                    TotalSum2 = TotalSum2 + digitBy2S4;
                }
                UltimateSum = TotalSum1 + TotalSum2;

                if (UltimateSum % 10 == 0)
                {
                    printf("VISA\n");
                    return 0;
                }
                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }

        }


    }


    //For VISA(13  digits):
    //find the front number.             //Testing:no result!!
    if (digit == 13)
    {
        for (int k = 0; k < 13-1; k++)
        {
            N /= 10;
        }
        if (N == 4)
        {
            Index = 14;
            TotalSum1 = 0;
            for (int u = 0; u < 6; u++)
            {
                Index -= 2;
                Power1 = pow(10,Index);
                Power2 = pow(10,(Index - 1));

                DigitBy2S1 = NN / Power1;             //find the one of the important value for removing the right part
                DigitBy2S2 = DigitBy2S1 * Power1;    //remove the right part
                DigitBy2S3 = NN - DigitBy2S2;         //remove the left part
                DigitBy2S4 = DigitBy2S3 / Power2;    //find the digit number
                DigitBy2S5 = DigitBy2S4 * 2;         //double the digit found before.
                if (DigitBy2S5 >= 10)                //When number>=10,like 14,break it down into 1 and 4
                {
                    DigitBy2S6 = DigitBy2S5 - 10;
                    Sum1 = 1 + DigitBy2S6;
                    TotalSum1 = TotalSum1 + Sum1;
                }
                if (DigitBy2S5 < 10)                 //When number <10,add it into the sum.
                {
                    TotalSum1 = TotalSum1 + DigitBy2S5;
                }

            }



            index = 15;
            TotalSum2 = 0;
            for (int g = 0; g < 7; g++)              //for the rest of digit that do not need to double.
            {
                index -= 2;
                power1 = pow(10,index);
                power2 = pow(10,(index - 1));

                digitBy2S1 = NN / power1;             //find the one of the important value for removing the right part
                digitBy2S2 = digitBy2S1 * power1;    //remove the right part
                digitBy2S3 = NN - digitBy2S2;         //remove the left part
                digitBy2S4 = digitBy2S3 / power2;    //find the digit number,which is digitBy2S4
                TotalSum2 = TotalSum2 + digitBy2S4;
            }
            UltimateSum = TotalSum1 + TotalSum2;
            if(UltimateSum % 10 == 0)
            {
                printf("VISA\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
    }
//////////mv to above

}