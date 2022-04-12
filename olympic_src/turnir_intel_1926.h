#ifndef TURNIR_INTEL_1926_H
#define TURNIR_INTEL_1926_H

#include <QStringList>
#include <math.h>
#include <QDebug>

struct BigInt
{
    QString num;
    QString parts[100];
    int n_parts;
    BigInt()
    {
        num="0";
        n_parts=1;
        parts[0] = "0";
        for(int i=0; i < 100; i++)
            parts[i] = "0";
    }
    ~BigInt(){}
    BigInt(QString number)
    {
        for(int i=0; i < 100; i++)
            parts[i] = "0";
        Init(number);
    }
    void Init(QString number)
    {
        num = number;
        int n = number.length() / 9;
        int r = number.length() % 9;
        for(int i=1; i <= n; i++)
        {
            parts[i-1] = number.midRef(number.length() - i*9,9).toString();
        }
        parts[n] = number.midRef(0,r).toString();
        n_parts = n;
    }
    BigInt(const BigInt& B)
    {
        Init(B.num);
    }
//    BigInt operator=(BigInt B)
//    {
//        Init(B.num);
//    }


    int getRemainder(int d)
    {
        int remainders[100];
        int chastnoe[100];
        for(int i=0; i < 100; i++)
        {
            remainders[i] = 0;
        }
        for(int i=0; i <= n_parts; i++)
        {
            remainders[i] = parts[i].toInt() % d;
            chastnoe[i] = parts[i].toInt() / d;
        }

          uint64_t r;

          r = remainders[n_parts];
          for(int i=n_parts; i > 0; i--)
          {
            r = r * ::pow(10,9) + remainders[i-1];
            r = r%d;
          }

        return r;
    }


    BigInt operator+(BigInt B)
    {
        BigInt result;
        int n_partsM = qMax(n_parts, B.n_parts);
        uint64_t prev_reg=0;
        for(int i=0; i <= n_partsM; i++)
        {
            uint64_t a = parts[i].toInt();
            uint64_t b = B.parts[i].toInt();

            QString res = QString::number(a+b+prev_reg);
            if(res.length() > 9)
                prev_reg = res.left(res.length()-9).toInt();
            else {
                prev_reg = 0;
            }
            result.n_parts = i;
            result.parts[i] = res.right(9);
        }
        //padding zeroes
        for(int i=0; i <= n_partsM; i++)
        {
            if((result.parts[i+1]!="0")&&(result.parts[i].length()!=9))
            {
               int num_zeroes = 9 - result.parts[i].length();
               for(int j=0; j < num_zeroes; j++)
                   result.parts[i] = "0" + result.parts[i];
            }
        }
        result.join();
        return result;
    }
    int getNParts()
    {
        for(int i=0; i < 100; i++)
            if(parts[i]=="0")
                return i-1;
        return 0;
    }
    bool operator>(BigInt B)
    {

        int n_partsM = qMax(getNParts(), B.getNParts());
        int sign=1;
        int sign2=1;
        if( parts[n_partsM][0] != '-' && num[0] == '-')
           sign = -1;
        if( B.parts[n_partsM][0] != '-' && B.num[0] == '-')
           sign2 = -1;
        if(n_partsM==0)
        {
            return parts[n_partsM].toInt()*sign > B.parts[n_partsM].toInt()*sign2;
        }
        // compare numbers
        BigInt* BB = &B;
        BigInt* AA = this;

        if( AA->parts[n_partsM].toInt()*sign > BB->parts[n_partsM].toInt()*sign2 )
        {
           return true;
        }
        return false;
    }
    QString int2bin(int i)
    {
        QString result;
        for(int bit=0; bit<32; bit++)
            result+=QString::number( (i>>bit)&0x1);
        return result;
    }
    uint bin2int(QString s)
    {
        uint result=0;
        for(int bit=0; bit<32; bit++)
            if(s[bit]=='1')
              result = result | (1 << bit);
        return result;
    }
    QString toBin()
    {
        BigInt d = *this;
        QString s;
        while (d.num.toInt()!=0)
        {

            if(d.getRemainder(2)==1)
                s+="1";
            else {
                s+="0";
            }
            d = d / 2;
        }
        return s;
    }
    BigInt fromBin2(QString s)
    {
        BigInt result;
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]=="1")
                result = result + pow(2,i);
        }
        return result;
    }

    void fromBin(QString s)
    {
        n_parts = s.length()/32;
        for(int i=0; i < n_parts; i++)
        {
           qDebug() << s.mid(i*32,32);
           uint I = bin2int(s.mid(i*32,32));
           parts[n_parts-i] = QString::number(I);
        }
        join();
    }

    BigInt operator/(int B)
    {
        BigInt result;
//        for(int i=0; i <= n_parts; i++)
//        {
//            result.parts[i] = QString::number(parts[i].toInt()/B);
//            if((result.parts[i].length()<9) && (i < n_parts))
//            {
//                for(int j=0; j < 9 - result.parts[i].length(); j++)
//                  result.parts[i] = "0"+result.parts[i];
//            }
//        }
//        if(parts[1].toInt() < B)
//        {
//            QString n = parts[1] + parts[0];
//            quint64 i = n.toLongLong();
//            result.Init(QString::number(i/B));
//            return result;
//        }
//        result.n_parts = n_parts;
//        result.join();
        QString chastnoe;
        int j=0;
        for(j=0; j < 1000; j++)
            if(j * B > QString(num[0]).toInt())
                break;
        chastnoe+=QString::number(j-1);
        QString s = QString::number(QString(num[0]).toInt()-(j-1)*B);
        for(int i=1; i < num.length(); i++)
        {
            s+=num[i];
            int j=0;
            for(j=0; j < 1000; j++)
                if(j * B > s.toInt())
                    break;
            chastnoe+=QString::number(j-1);
            s = QString::number(s.toInt()-(j-1)*B);
        }
        result.Init(chastnoe);
        return result;
    }
    BigInt pow(int base, int p)
    {
        BigInt basen = BigInt(QString::number(base));
        BigInt result = basen;
        for(int i=0; i<p-1; i++)
        {
            result =  result * basen;
            //qDebug() << result.num;
        }
        if(p==0)
          result.num = "1";
        result.Init(result.num);
        return  result;
    }
    BigInt abs()
    {
        if(num[0]=='-')
            return BigInt(num.mid(1,num.length()-1));
        else return *this;
    }

    BigInt operator/(BigInt B)
    {
       //test bin2int
//        qDebug() << "int2bin(97654321)=" << int2bin(97654321);
//        qDebug() << "bin2int(10001100011010000100101110100000)" << bin2int("10001100011010000100101110100000");
//        QString s = toBin();
//        //divide by 2
//        QString s2 = s.mid(1,s.length()) + "0";
//        qDebug() << "toBin() " << s;
//        //fromBin(s2);
//        //qDebug() << "fromBin() " << num;
//        qDebug() << " div 2" << (*this / 2).num;

//        qDebug() << "pow(10,6)" << pow(10,6).num;
//        return BigInt();

       if( B > *this)
           return BigInt();
       BigInt result,result2, result3;
       // diffirence in digits
       int dif = num.length() - B.num.length();

       BigInt min = pow(10, dif-1);
       BigInt max = pow(10, dif+1);

       BigInt a,b,c;
       int iters=0;
       while(max > min)
       {
           c = min + (max-min)/2;
           b = max;
           a = min;

           result = *this - (B * c);
           result2 = *this - (B * b);
           result3 = *this - (B * a);
//           qDebug() << min.num << "-" << max.num;
//           qDebug() << result.num;
//           qDebug() << result2.num;
//           qDebug() << result3.num;
//           qDebug() << "-------------------";
//           qDebug() <<(result*result3).num;
           if(BigInt("0") > (result*result3))
           {
               max = min + (max-min)/2;
               //min = p1;
           }
            if(BigInt("0") > (result*result2))
            {
               //max = p2;
               min = min + (max-min)/2;
           }
           if((max-min).num.toInt() == 1)
               break;
           iters++;

       }
       qDebug() << "iters=" << iters;
       return min;
    }

    BigInt operator*(BigInt B)
    {
        BigInt result;
        int n_partsM = qMax(n_parts, B.n_parts);
        // compare numbers
        BigInt* BB = &B;
        BigInt* AA = this;

        if( AA->parts[n_partsM-1].toInt() < BB->parts[n_partsM-1].toInt() )
        {
            AA = &B;
            BB = this;
        }
        int res_len = BB->num.length()+AA->num.length();

        for(int i=0; i < BB->num.length() ; i++)
        {
            BigInt C;
            int prev_reg=0;

            for(int k=0; k <= res_len; k++)
                C.num[k] = '0';

            for(int j=0; j < AA->num.length() ; j++)
            {
                int c = QString(AA->num[AA->num.length()-j-1]).toInt() * QString(BB->num[BB->num.length()-i-1]).toInt()+prev_reg;
                if( (c/10) == 0 )
                {
                   C.num[res_len-j-i] = QString::number(c)[0];
                   prev_reg = 0;
                }
                else
                {
                    C.num[res_len-j-i] = QString::number(c%10)[0];
                    prev_reg = c/10;
                }


            }
            C.num[res_len-AA->num.length()-i] = QString::number(prev_reg)[0];
            //C.Init(C.num);
            result = result + C;

        }
        //sign
        if( num[0] == '-' && B.num[0] !='-')
            result.num = "-" + result.num;
        if( num[0] != '-' && B.num[0] =='-')
            result.num = "-" + result.num;
        return result;
    }
    BigInt operator-(BigInt B)
    {
        BigInt result;
        int n_partsM = qMax(n_parts, B.n_parts);
        int64_t prev_reg=0;
        // compare numbers
        BigInt* BB = &B;
        BigInt* AA = this;
        bool reverse_flag=false;

        if( AA->parts[n_partsM].toInt() < BB->parts[n_partsM].toInt() )
        {
            AA = &B;
            BB = this;
            reverse_flag = true;
        }


        for(int i=0; i <= n_partsM; i++)
        {
            int64_t a = AA->parts[i].toInt();
            int64_t b = BB->parts[i].toInt();

            int64_t c = a-b-prev_reg;
            if(c < 0 && AA->parts[i+1].toInt()>0)
            {
                 QString s = "1" + AA->parts[i];
                 a = s.toLongLong();
                 c = a-b-prev_reg;
                 prev_reg=1;
            }
            else
               prev_reg=0;
            QString res = QString::number(c);


            result.n_parts = i;
            result.parts[i] = res.right(9);

        }
        //padding zeroes
        for(int i=0; i <= n_partsM; i++)
        {
            if((result.parts[i+1]!="0")&&(result.parts[i].length()!=9))
            {
               int num_zeroes = 9 - result.parts[i].length();
               for(int j=0; j < num_zeroes; j++)
                   result.parts[i] = "0" + result.parts[i];
            }
        }

        result.join();
        if(reverse_flag)
            result.num = "-"+result.num;
        return result;
    }
    void join()
    {
        num = "";
        bool flag=false;
        for(int i=n_parts; i >= 0; i--)
        {

            if(parts[i]!="0" && parts[i].length()>0)
            {
              num+=parts[i];
              flag = true;
            }
            if(parts[i]=="0" && flag)
            {
                num+="000000000";
            }

        }
    }

};

class Turnir_intel_1926
{
public:
    BigInt n;
    Turnir_intel_1926();
    void ParseInput(QStringList list);
    int getRemain(int divider);
    int changeDigit(int k, int b);
};

#endif // TURNIR_INTEL_1926_H
