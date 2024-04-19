void accessDYJetsToLL() {
    TFile* file = TFile::Open("root://eospublic.cern.ch//eos/opendata/cms/derived-data/AOD2NanoAODOutreachTool/DYJetsToLL.root");
    if (file && !file->IsZombie()) {
        cout << "Arquivo aberto com sucesso!" << endl;
        file->ls();  // Lista os objetos no arquivo ROOT.
    } else {
        cout << "Falha ao abrir o arquivo." << endl;
    }
}