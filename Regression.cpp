/***一元线性回归（Simple linear regression）求解***
 * Name:Wang Junhe
 * Time:2021,09,04
 * Method:SDG
 * Language:C++
 * Email:1619356172@qq.com
 * **********************************************/

#include <vector>
#include <iostream>
using namespace std;
class Regression{
public:
//初始参数
double w=-2.0;
double b = 4;
//计算y
double val(double x){
    return w*x+b;
}
//计算梯度
vector<double> grad(double y,double y_ref,double x){
    vector<double> tmp;
    tmp.push_back(x*(y-y_ref));//w's grad
    tmp.push_back(y-y_ref);//d's grad
    //cout<<x<<"space"<<y<<"space"<<y_ref<<"space"<<tmp[0]<< "space"<<tmp[1]<<endl;
    return tmp;}
//生成数据
vector<vector<double>> rand_val(double w_ref,double b_ref,double start,double end,int n){
    double e = 0.0;
    double unit_x = (end-start)/n;
    vector<vector<double>> val(n);
    while(n--){
        e = -4 + (double)(rand()) /RAND_MAX * (4 - (-4));
        val[n].push_back(start+n*unit_x);
        val[n].push_back(w_ref*val[n][0]+b_ref+e);
        //cout<<"x"<<val[n][0]<<"y_ref"<<val[n][1]<<endl;
    }
    return val;
}
//训练函数
void train(vector<vector<double>> date,double alpha_w,double alpha_b){
    int num = date.size();
    vector<double> tmp;
    double x(0.0),y(0.0),y_ref(0.0);
    for(int i = 0;i<num;i++){
        x = date[i][0];
        y = val(x);
        y_ref = date[i][1];
        tmp = grad(y,y_ref,x);
        w = w-alpha_w*tmp[0];
        b = b-alpha_b*tmp[1];
    }
}
};
int main(){
    //参数设置
    Regression sol;
    double w_init = sol.w;
    double b_init = sol.b;
    double w_ref = 3.0;
    double b_ref = 2.0;
    double sample = 500;
    double start_sample = -10;
    double end_sample = 10.0;
    double alpha_w = 0.002;
    double alpha_b = 0.01;

    vector<vector<double>> date=sol.rand_val(w_ref, b_ref, start_sample, end_sample, sample);
    sol.train(date,alpha_w,alpha_b);

    cout<<"-------------一元线性回归bySGD-------------"<<endl;
    cout<<"sample_num=500    alpha_w="<<alpha_w<<"    alpha_b="<<alpha_b<<"\n"<<endl;
    cout<<"init_value:   w_init="<<w_init<<"     b_init="<<b_init<<"\n"<<endl;
    cout<<"real_value:   w_ref="<<w_ref<<"      b_ref="<<b_ref<<endl;
    cout<<"train_result:"<<" w="<<sol.w<<"    b="<<sol.b<<"\n"<<endl;
    system("pause");
    return 0;
} 