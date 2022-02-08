double  average(vector<double> const& v)
{
    double count = static_cast<float>(v.size());
    return reduce(v.begin(), v.end()) / count;
}


double Covariance(vector<double> x, vector<double> y, int ddof, int offset)
{
    double X_av = average(x);
    double Y_av = average(y);
    double temp;
    for (int i = 0; i < x.size() - offset)
    {
        temp += (x[i]-X_av)*(y[i+offset]-Y_av)
    }
    return temp/(x.size()-ddof)
}

