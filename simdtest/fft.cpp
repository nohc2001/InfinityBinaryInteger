#include <iostream>
#include <complex>
#include <math.h>
#include <valarray>
#include <vector>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
constexpr double PI = 3.14159265358979323846;

using namespace std;

typedef struct SwapPair{
    unsigned int index0;
    unsigned int index1;

    SwapPair(){}
    SwapPair(int i0, int i1){
        index0 = i0;
        index1 = i1;
    }
    ~SwapPair(){}
};

typedef struct OperPair{
    Complex w;
    unsigned int t_index;
    unsigned int u_index;

    OperPair(){
    }
    OperPair(Complex pw, unsigned int ti, unsigned int ui){
        w = pw;
        t_index = ti;
        u_index = ui;
    }
    ~OperPair(){}
};

vector<OperPair> fftoper;
vector<SwapPair> fftswap;

// Function to reverse bits of num
inline unsigned int reverseBits(unsigned int num, int bits)
{
	unsigned int reverse_num = 0;
	for (int i = 0; i < bits; i++)
	{
		if ((num & (1 << i)))
			reverse_num |= 1 << ((bits - 1) - i);
	}
	return reverse_num;
}

void fft(CArray &x)
{
    const size_t N = x.size();
    const size_t M = log2(N);

    // bit-reversed permutation
    for (size_t i = 0; i < N; i++)
    {
        size_t j = reverseBits(i, M);
        if (i < j)
            std::swap(x[i], x[j]);
    }

    // butterfly updates
    for (size_t s = 1; s <= M; s++)
    {
        size_t m = 1 << s;
        Complex wm = std::polar(1.0, -2 * PI / m);

        for (size_t k = 0; k < N; k += m)
        {
            Complex w = 1;
            for (size_t j = 0; j < m / 2; j++)
            {
                Complex t = w * x[k + j + m / 2];
                Complex u = x[k + j];

                x[k + j] = u + t;
                x[k + j + m / 2] = u - t;
                w *= wm;
            }
        }
    }
}

void fft_addStamp(unsigned int dataSiz)
{
    fftoper.clear();
    fftswap.clear();
    const size_t N = dataSiz;
    const size_t M = log2(N);

    // bit-reversed permutation
    for (size_t i = 0; i < N; i++)
    {
        size_t j = reverseBits(i, M);
        if (i < j){
            fftswap.push_back(SwapPair(i, j));
        }
    }

    // butterfly updates
    for (size_t s = 1; s <= M; s++)
    {
        size_t m = 1 << s;
        Complex wm = std::polar(1.0, -2 * PI / m);

        for (size_t k = 0; k < N; k += m)
        {
            Complex w = 1;
            for (size_t j = 0; j < m / 2; j++)
            {
                fftoper.push_back(OperPair(w, k + j + m / 2, k + j));
                w *= wm;
            }
        }
    }
}

void fft_useStamp(CArray& x){
    Complex temp;
    for(int i=0;i<fftswap.size();++i){
        SwapPair& sp = fftswap.at(i);
        unsigned int index0 = sp.index0;
        unsigned int index1 = sp.index1;
        temp = x[index0];
        x[index0] = x[index1];
        x[index1] = temp;
    }

    for(int i=0;i<fftoper.size();++i){
        OperPair& op = fftoper.at(i);
        Complex w = op.w;
        unsigned int ti = op.t_index;
        unsigned int ui = op.u_index;
        Complex t = w * x[ti];
        Complex u = x[ui];
        x[ui] = u + t;
        x[ti] = u - t;
    }
}

// Iterative in-place bit-reversed Cooley-Tukey IFFT
inline void ifft(CArray &x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    fft(x);

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}

inline void ifft_useStamp(CArray &x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);

    // forward fft
    fft_useStamp(x);

    // conjugate the complex numbers again
    x = x.apply(std::conj);

    // scale the numbers
    x /= x.size();
}

// Fast Convolution
inline void fastConvolusion(CArray &a, CArray &b, Complex *resultdata_out, int rsiz)
{
    int maxsiz = (a.size() > b.size()) ? a.size() : b.size();

    Complex *adata = new Complex[maxsiz];
    Complex *bdata = new Complex[maxsiz];
    for (int i = 0; i < maxsiz; ++i)
    {
        adata[i] = complex<double>();
        bdata[i] = complex<double>();
        adata[i] = a[i];
        bdata[i] = b[i];
    }
    CArray aarr(adata, maxsiz);
    CArray barr(adata, maxsiz);
    fft(aarr);
    fft(barr);

    for (int i = 0; i < maxsiz; ++i)
    {
        aarr[i] = aarr[i] * barr[i];
    }
    ifft(aarr);

    int m = 0;
    if (maxsiz >= rsiz)
        m = maxsiz;
    else
        m = rsiz;
    for (int i = 0; i < m; ++i)
    {
        resultdata_out[i] = aarr[i];
    }

    delete[] adata;
    delete[] bdata;
}

int main(){
    CArray carr(1024);
    CArray carr2(1024);
    unsigned int* arr = new unsigned int[1024];

    while (true)
    {
        for (int i = 0; i < 1024; ++i)
        {
            arr[i] = (unsigned int)rand();
            double d = (double)(arr[i]);
            carr[i] = Complex(d, 0.0);
            carr2[i] = Complex(d, 0.0);
            // cout << (int)arr[i] << ", ";
        }
        // cout << endl;
        // cout << endl;

        fft_addStamp(1024);
        fft_useStamp(carr);

        // for(int i=0;i<1024;++i){
        // cout << "(" << carr[i].real() << ", " << carr[i].imag() << "), ";
        //}
        // cout << endl;
        // cout << endl;

        ifft_useStamp(carr);

        bool b = true;
        int error = 0;
        for (int i = 0; i < 1024; ++i)
        {
            unsigned int c = (unsigned int)(carr[i].real() + 0.5);
            // cout << (int)c << ", ";
            // cout << carr[i].real() << ", ";
            b = b & (c == arr[i]);
            error += c - arr[i];
        }
        // cout << endl;
        // cout << endl;

        if (b)
        {
            cout << "perfect!! : " << error << endl;
        }
        else
        {
            cout << "error!! : " << error << endl;
        }
    }

    return 0;
}