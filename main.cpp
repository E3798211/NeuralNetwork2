#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;

void NetworkAction(int letter_input_bits[15], int s_neurons[15],
                            double sinapses[10][15], double r_neurons_out[10], double step);
void WeightsCorrection(int letter_input, int s_neurons[15],
                            double sinapses[10][15], double r_neurons_out[10], double speed);
double ActivationFunction(double x);

void ReadFunc(int letter_bits[15]);

int main(int argc, char *argv[])
{
    //Letter's bits

    int letters[10][15] = {
        {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}
    };

    /*
     * Neural Network==================================
    */

    //S-neurons

    int S_neurons[15];

    //Activation function

    double bias = 0.5;

    //Network's answer

    double network_answer[10];

    //Sinapses

    double weights[10][15] = {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}
    };

    /*
     * Trainig========================================
    */

    int training_time = 100000;
    double speed = 0.4;
    int letter;

    for(int i = 0; i < training_time; i++){
        //Choosing letter to show
        letter = rand() % 10;
        //Giving it to Network
        NetworkAction(letters[letter], S_neurons, weights, network_answer, bias);
        //Correcting weights
        WeightsCorrection(letter, S_neurons, weights, network_answer, speed);
    }

    /*
     * Action
    */

    /*
    //Check print
    for(int i = 0; i < 10; i++){
        NetworkAction(letters[i], S_neurons, weights, network_answer, bias);
        cout << "\nResults for " << i << "\n";
        for(int k = 0; k < 10; k++)
            cout << i << " = " << k << "?\t" << network_answer[k] << "\n";
    }
    */

    /*
     *
     * And here's fun!
     *
     *
    */

    //Broken letters
    int wrong01[15] = {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0};
    int wrong02[15] = {1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1};
    int wrong11[15] = {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0};
    int wrong12[15] = {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1};
    int wrong21[15] = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1};
    int wrong22[15] = {0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0};
    int wrong31[15] = {1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
    int wrong32[15] = {1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0};
    int wrong41[15] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1};
    int wrong42[15] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1};
    int wrong51[15] = {1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1};
    int wrong52[15] = {1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1};
    int wrong61[15] = {1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1};
    int wrong62[15] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0};
    int wrong71[15] = {1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    int wrong72[15] = {1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1};
    int wrong81[15] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1};
    int wrong82[15] = {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0};
    int wrong91[15] = {0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1};
    int wrong92[15] = {1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1};

    int user_num[15] = {1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1};

    cout << "And here's fun!\n";
    //Network's map
    cout << "Network's map\n" << endl;
    int counter = 0;
    for(int i = 0; i < 15; i++){
        printf("%10.5f", weights[8][i]);
        if(++counter % 3 == 0)    cout << endl;
    }
    cout << endl;

    //NetworkAction(wrong41, S_neurons, weights, network_answer, bias);

    ReadFunc(user_num);
    NetworkAction(user_num, S_neurons, weights, network_answer, bias);
    //Real values
    cout << "Real values\n" << endl;
    for(int i = 0; i < 10; i++)
        cout << i << "\t" << network_answer[i] << endl;
    //Normalization
    double norm_sum = 0;
    for(int i = 0; i < 10; i++)
        norm_sum += network_answer[i];
    for(int i = 0; i < 10; i++)
        network_answer[i] = network_answer[i] * 100 / norm_sum;
    //Print again
    cout << "\nPercents:\n" << endl;
    cout.setf(ios::fixed);
    for(int i = 0; i < 10; i++)
        cout << i << "\t" << network_answer[i] << endl;
    cout.setf(ios::fixed);
}

void NetworkAction(int letter_input_bits[15], int s_neurons[15], double sinapses[10][15], double r_neurons_out[10], double step)
{
    double summary = 0;
    //Input
    for(int i = 0; i < 15; i++)
        s_neurons[i] = letter_input_bits[i];
    //Finding answer for every R-neuron
    for(int i = 0; i < 10; i++){
        //Finding i-neuron answer
        //Finding summary
        for(int k = 0; k < 15; k++)
            summary += s_neurons[k]*sinapses[i][k];
        //Pass through Activation function

        /*
        if(summary > step)  r_neurons_out[i] = 1;
        else                r_neurons_out[i] = 0;
        */

        r_neurons_out[i] = ActivationFunction(summary);
        //Seting to zero
        summary = 0;
    }
}


void WeightsCorrection(int letter_input, int s_neurons[15],
                       double sinapses[10][15], double r_neurons_out[10], double speed)
{
    double target;
    double delta;
    //Running through every neuron's sinaps
    //i-neuron has to react only on letter "i"
    for(int i = 0; i < 10; i++){
        //Checking answer

        /*
        if(letter_input == i && r_neurons_out[i] != 1){
            for(int k = 0; k < 15; k++){
                if(s_neurons[k] == 1)   sinapses[i][k] += speed;
            }//increase
        }else if(letter_input != i && r_neurons_out[i] == 1){
            for(int k = 0; k < 15; k++){
                if(s_neurons[k] == 1)   sinapses[i][k] -= speed;
            }//decrese
        }//Otherwise everything is OK
        */
        //Finding delta
        if(letter_input == i)   target = 1;
        else                    target = 0;

        delta = target - r_neurons_out[i];
        //Correcting weights
        for(int k = 0; k < 15; k++)
            sinapses[i][k] += speed*delta*s_neurons[k];
    }
}

double ActivationFunction(double x)
{
    double a = 1 + exp(-x);
    return 1/a;
}


void ReadFunc(int letter_bits[15]){

    ifstream fstr("1");
    //int letter_bits[15];
    //Reading

    string str;
    string tmp;
    char c [1];

    while (!fstr.eof()){
        str.append(tmp);
        fstr >> tmp;
    }

    //cout << str << endl;

    for(int i = 0; i < 15; i++){
        c[0] = str[i];
        letter_bits[i] = atoi(c);
    }
}


