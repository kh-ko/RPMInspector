#ifndef INTERPOLATIONUTIL_H
#define INTERPOLATIONUTIL_H
#include <QObject>
#include <QtMath>

class InterpolationUtil
{
public:
    InterpolationUtil(){}
    ~InterpolationUtil(){}

    static int monotonicCubicHermiteSpline(int x, QList<double>xList, QList<double>yList)
    {
        QList<double> dxList;
        QList<double> dyList;
        QList<double> slopeList;
        QList<double> c1s;
        QList<double> c2s;
        QList<double> c3s;

        for(int i = 1; i < xList.size(); i ++)
        {
            dxList.append(xList[i] - xList[i-1]);
            dyList.append(yList[i] - yList[i-1]);
            slopeList.append(dyList.last()/ dxList.last());
        }

        c1s.append(slopeList[0]);
        for (int i = 1; i < dxList.size(); i++)
        {
            double m     = slopeList[i-1];
            double mNext = slopeList[i];

            if(m*mNext <= 0)
            {
                c1s.append(0);
            }
            else
            {
                double dx_    = dxList[i-1];
                double dxNext = dxList[i];
                double common = dx_ + dxNext;

                c1s.append(3*common/((common + dxNext)/m + (common + dx_)/mNext));
            }
        }

        c1s.append(slopeList[slopeList.size() - 1]);

        // Get degree-2 and degree-3 coefficients
        for (int i = 1; i < c1s.size(); i++)
        {
            double c1 = c1s[i -1];
            double m_ = slopeList[i-1];
            double invDx = 1 / dxList[i-1];
            double common_ = c1 + c1s[i] - m_ - m_;
            c2s.append((m_ - c1 - common_)*invDx); c3s.append(common_*invDx*invDx);
        }

        if(x < (int)xList[0])
        {
            return 0;
        }

        if(x >= (int)xList[xList.size()-1])
        {
            return qRound(yList[xList.size()-1]);
        }

        int low = 0;
        int mid = 0;
        int high = c3s.size() - 1;

        while (low <= high)
        {
            mid = qFloor(0.5*(low + high));
            double xHere = xList[mid];

            if (xHere < (double)x)
            {
                low = mid + 1;
            }
            else if(xHere > (double)x)
            {
                high = mid - 1;
            }
            else{
                return qRound(yList[mid]);
            }
        }

        int i = 0 < high ? high : 0;

        // Interpolate
        double diff = x - xList[i];
        double diffSq = diff*diff;

        double yValue = yList[i] + c1s[i]*diff + c2s[i]*diffSq + c3s[i]*diff*diffSq;
        return qRound(yValue);
    }
};

#endif // INTERPOLATIONUTIL_H
