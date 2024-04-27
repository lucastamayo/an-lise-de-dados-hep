void ex1(){

TCanvas *c1 = new TCanvas("c1", "Canvas", 600, 400);
TF1 *func = new TF1("func", "[0]*sin([1]*x)/x", 0, 10); // Range de 0 a 10
func->SetParameters(1, 2); // Definindo p0 = 1, p1 = 2
func->SetLineColor(kBlue); // Definindo a cor da linha para azul

func->Draw();

c1->SaveAs("ex1.png");

double val_x1 = func->Eval(1);
std::cout << "Valor da função para x=1: " << val_x1 << std::endl;

double deriv_x1 = func->Derivative(1);
std::cout << "Valor da derivada da função para x=1: " << deriv_x1 << std::endl;

double integral_0_3 = func->Integral(0, 3);
std::cout << "Valor para a integral de 0 a 3 da função: " << integral_0_3 << std::endl;


}