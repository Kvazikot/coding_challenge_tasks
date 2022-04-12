#include "polynom1503.h"
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QElapsedTimer>
#include <math.h>

#define JMAX 20 //Set to maximum number of iterations.
/*
 * Using the Newton-Raphson method, find the root of a function known to lie in the interval
[x1, x2]. The root rtnewt will be refined until its accuracy is known within ±xacc. funcd
is a user-supplied routine that returns both the function value and the first derivative of the
function at the point x.
*/
float rtnewt(void (*funcd)(float, float *, float *, const float *), const float* a, float x1, float x2,float xacc)
{
    int j;
    float df,dx,f,rtn;
    rtn=0.5*(x1+x2);
    //Initial guess.
    for (j=1;j<=JMAX;j++) {
        (*funcd)(rtn,&f,&df, a);
        dx=f/df;
        rtn -= dx;
        //if ((x1-rtn)*(rtn-x2) < 0.0)
            //qDebug("Jumped out of brackets in rtnewt");
    }
    if (fabs(dx) < xacc) return rtn;
    //Convergence.
qDebug("Maximum number of iterations exceeded in rtnewt");
return 0.0; // Never get here.
}

void polyf(float x, float* f, float* df, const float* a)
{
    int n = sizeof(a)/sizeof(float);
    *f = 0;
    for(int i=0; i < n; i++)
    {
        *f+=a[i] * pow(x, n-i);
    }
    *f+=a[n];
    *df = 0;
    for(int i=0; i < n; i++)
    {
        *df+=a[i] * (n-i)* pow(x, n-i-1);
    }


}


std::vector<float> Polynom1503::scanForRoots(float* a, float x1, float x2, float dx)
{
    std::map<float,bool> roots;

    for(float i=x1; i < x2; i+=dx)
    {
        float result = rtnewt(polyf, a, i, i+dx, 10e-6);
        roots[result] = true;
    }

    std::vector<float> rootsv;
    for(auto i=roots.begin(); i!=roots.end(); i++)
        rootsv.push_back((*i).first);

    std::sort(rootsv.begin(), rootsv.end(),
        [&](float a, float  b) -> bool
    {
              return a < b;
    });

    auto last = std::unique(rootsv.begin(), rootsv.end(),
        [&](float a, float  b) -> bool
    {
              return (fabs(a - b) < 10e-6) ;
    });
    rootsv.erase(last, rootsv.end());


    return rootsv;
}


//--------------------------- UNIT TEST -----------------------------------------

void Polynom1503::parseInput(QStringList input)
{
    n = input[0].toInt();
    a = new float[n+1];
    for(int i=0; i < n+1; i++)
    {
        a[i] = input[i+1].toFloat();
    }
}

void Polynom1503::TestRootFinding1()
{
    QStringList input;
    input.append("3");
    input.append("1");
    input.append("-2");
    input.append("-1");
    input.append("1");
    parseInput(input);
    QElapsedTimer timer;

    timer.start();

    // scan for roots
    std::vector<float> roots = scanForRoots(a,-100,100,10);
    dbg_stream << "\n" << "timer " << timer.elapsed();


    int j=0;
    for(auto i=roots.begin(); i!=roots.end(); i++)
    {
         dbg_stream << "\n" << "root " << j << " " << qSetRealNumberPrecision( 10 ) << (*i);
        j++;
    }
}

void Polynom1503::TestRootFinding2()
{
    QStringList input;
    input.append("2");
    input.append("1");
    input.append("0");
    input.append("-4");
    parseInput(input);
    QElapsedTimer timer;

    timer.start();

    // scan for roots
    std::vector<float> roots = scanForRoots(a,-100,100,10);
    dbg_stream << "\n" << "timer " << timer.elapsed();


    int j=0;
    for(auto i=roots.begin(); i!=roots.end(); i++)
    {
         dbg_stream << "\n" << "root " << j << " " << qSetRealNumberPrecision( 10 ) << (*i);
        j++;
    }
}

void Polynom1503::TestPolyFAndRt()
{
    float f, df;
    QStringList input;
    input.append("3");
    input.append("1");
    input.append("-2");
    input.append("-1");
    input.append("1");
    parseInput(input);

    //test the polyf
    polyf(0, &f, &df, a);
    dbg_stream << "\n" << "f=" << f;
    dbg_stream << "\n" << "df=" << df;
    polyf(1, &f, &df, a);
    dbg_stream << "\n" << "f=" << f;
    dbg_stream << "\n" << "df=" << df;
    polyf(2, &f, &df, a);
    dbg_stream << "\n" << "f=" << f;
    dbg_stream << "\n" << "df=" << df;
    dbg_stream << "\n" << sizeof(a)/sizeof(float);
    dbg_stream << "\n" << "-----------result--------------";
    float result = rtnewt(polyf, a, -10, 12, 10e-6);
    dbg_stream << "\n" << result << " " << result;
}


Polynom1503::Polynom1503()
{
    QFile log("Polynom1503.log");

    if (!log.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return;
    }
    else
    {
        qDebug() << "File opened";
    }


    dbg_stream.setDevice(&log);

    dbg_stream << "\n" << "TestPolyFAndRt";
    TestPolyFAndRt();

    dbg_stream << "\n" << "================================";
    dbg_stream << "\n" << "TestRootFinding1";
    TestRootFinding1();
    dbg_stream << "\n" << "================================";


    dbg_stream << "\n" << "================================";
    dbg_stream << "\n" << "TestRootFinding2";
    TestRootFinding2();
    dbg_stream << "\n" << "================================";

    dbg_stream.seek(0);
    while( !dbg_stream.atEnd() )
    {
        qDebug() << dbg_stream.readLine();
    }

}
