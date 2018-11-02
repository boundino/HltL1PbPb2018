#include <TTree.h>
#define MAX_XB       20000

namespace objstructure
{
  class getDntuple
  {
  public:
    int     Dsize;
    float   PVz;

    float   Dpt[MAX_XB];
    float   Dy[MAX_XB];
    float   Dmass[MAX_XB];
    float   DsvpvDistance[MAX_XB];
    float   DsvpvDisErr[MAX_XB];
    float   Dchi2cl[MAX_XB];
    float   Dalpha[MAX_XB];
    float   Dgen[MAX_XB];

    float   Dtrk1Pt[MAX_XB];
    float   Dtrk2Pt[MAX_XB];
    float   Dtrk1Eta[MAX_XB];
    float   Dtrk2Eta[MAX_XB];
    float   Dtrk1PtErr[MAX_XB];
    float   Dtrk2PtErr[MAX_XB];
    float   Dtrk1PixelHit[MAX_XB];
    float   Dtrk2PixelHit[MAX_XB];
    float   Dtrk1StripHit[MAX_XB];
    float   Dtrk2StripHit[MAX_XB];

    getDntuple() { }
    getDntuple(TTree* root) { setbranchaddress(root); }
    ~getDntuple() { }
    
    void setbranchaddress(TTree* root)
    {
      root->SetBranchAddress("Dsize", &Dsize);
      root->SetBranchAddress("PVz", &PVz);
      root->SetBranchAddress("Dpt", Dpt);
      root->SetBranchAddress("Dy", Dy);
      root->SetBranchAddress("Dmass", Dmass);
      root->SetBranchAddress("DsvpvDistance", DsvpvDistance);
      root->SetBranchAddress("DsvpvDisErr", DsvpvDisErr);
      root->SetBranchAddress("Dchi2cl", Dchi2cl);
      root->SetBranchAddress("Dalpha", Dalpha);
      root->SetBranchAddress("Dgen", Dgen);

      root->SetBranchAddress("Dtrk1Pt", Dtrk1Pt);
      root->SetBranchAddress("Dtrk1Eta", Dtrk1Eta);
      root->SetBranchAddress("Dtrk1PtErr", Dtrk1PtErr);
      root->SetBranchAddress("Dtrk1PixelHit", Dtrk1PixelHit);
      root->SetBranchAddress("Dtrk1StripHit", Dtrk1StripHit);
      root->SetBranchAddress("Dtrk2Pt", Dtrk2Pt);
      root->SetBranchAddress("Dtrk2Eta", Dtrk2Eta);
      root->SetBranchAddress("Dtrk2PtErr", Dtrk2PtErr);
      root->SetBranchAddress("Dtrk2PixelHit", Dtrk2PixelHit);
      root->SetBranchAddress("Dtrk2StripHit", Dtrk2StripHit);
    }
    
    bool iscandsel(int j)
    {
      bool val = PVz < 15 && Dgen[j]==23333 && 
        TMath::Abs(Dy[j]) < 1 && DsvpvDistance[j]/DsvpvDisErr[j] > 2.5 && Dchi2cl[j] > 0.05 && Dalpha[j] < 0.12 &&
        Dtrk1Pt[j] > 6 && TMath::Abs(Dtrk1Eta[j]) < 1.5 && Dtrk1PtErr[j]/Dtrk1Pt[j] < 0.3 && Dtrk1PixelHit[j]+Dtrk1StripHit[j] >= 11 &&
        Dtrk2Pt[j] > 6 && TMath::Abs(Dtrk2Eta[j]) < 1.5 && Dtrk2PtErr[j]/Dtrk2Pt[j] < 0.3 && Dtrk2PixelHit[j]+Dtrk2StripHit[j] >= 11 ;
      return val;
    }
  };

}
