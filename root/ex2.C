void ex2() {
    // Lê os dados dos pontos dos arquivos
    ifstream dataFile("graphdata.txt");
    ifstream errorFile("graphdata_error.txt");

    // Conta quantos pontos temos
    int nPoints = 0;
    double x, y;
    while (dataFile >> x >> y) {
        ++nPoints;
    }

    // Reseta os ponteiros dos arquivos para o início
    dataFile.clear();
    dataFile.seekg(0, ios::beg);
    errorFile.clear();
    errorFile.seekg(0, ios::beg);

    // Cria arrays para armazenar os dados e erros
    double *xValues = new double[nPoints];
    double *yValues = new double[nPoints];
    double *exValues = new double[nPoints];
    double *eyValues = new double[nPoints];

    // Lê os dados e os erros e armazena nos arrays
    for (int i = 0; i < nPoints; ++i) {
        dataFile >> xValues[i] >> yValues[i];
        errorFile >> exValues[i] >> eyValues[i];
    }

    // Fecha os arquivos
    dataFile.close();
    errorFile.close();

    // Cria um gráfico de erros
    TGraphErrors *graph = new TGraphErrors(nPoints, xValues, yValues, exValues, eyValues);

    // Define o estilo dos pontos
    graph->SetMarkerStyle(21); // Estilo de ponto quadrado
    graph->SetMarkerColor(kBlack); // Cor dos pontos
    graph->SetLineColor(kBlue); // Cor da linha conectando os pontos

    // Desenha o gráfico
    TCanvas *c1 = new TCanvas("c1", "Graph with Errors", 200, 10, 700, 500);
    graph->Draw("AP"); // "A é relativo aos eixos (axis) e P aos pontos (points)"
    c1->SaveAs("ex2.png");
    // Limpa a memória
    delete [] xValues;
    delete [] yValues;
    delete [] exValues;
    delete [] eyValues;
}
