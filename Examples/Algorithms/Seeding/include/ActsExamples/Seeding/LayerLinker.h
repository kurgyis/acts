#ifndef __LAYER_LINKER_H__
#define __LAYER_LINKER_H__

#include <fstream>
#include <vector>
#include <map>

/*
//has index,src,dst,prob and flow
typedef struct LayerLink {
public:

  struct CompareFlow {
    bool operator()(const struct LayerLink& l1, const struct LayerLink& l2) {
      return l1.m_flow > l2.m_flow;
    }
  };

  //Not used anywhere?
  struct CompareProb {
    bool operator()(const struct LayerLink& l1, const struct LayerLink& l2) {
      return l1.m_prob > l2.m_prob;
    }
  };
  
  LayerLink(int idx, unsigned int d, unsigned int s, float p, float f) : m_index(idx), m_src(s), m_dst(d), m_prob(p), m_flow(f) {};
  ~LayerLink() {};

  int m_index;
  unsigned int m_src, m_dst;
  float m_prob, m_flow;
  
} LAYER_LINK;

//has fSeg and index
typedef struct LinkStat {
public:
  struct CompareStats {
    bool operator()(const struct LinkStat& l1, const struct LinkStat& l2) {
      return l1.m_fSeg > l2.m_fSeg;
    }
  };
    
LinkStat(float f, int i) : m_fSeg(f), m_index(i) {};

  float m_fSeg;
  int m_index;
  
} LINK_STAT;
*/

typedef class LayerLinker {
 public:
  LayerLinker(std::ifstream& linkFile, float threshold)
  {
    unsigned int nSources;

  linkFile.read((char*)&nSources, sizeof(nSources));

  int linkIndex=0;
  
  for(unsigned int idx=0;idx<nSources;idx++) {

    unsigned int src;
    float totalFlow;
    unsigned int nLinks;
    
    linkFile.read((char*)&src, sizeof(src));
    linkFile.read((char*)&totalFlow, sizeof(totalFlow));
    linkFile.read((char*)&nLinks, sizeof(nLinks));
    
    for(unsigned int k=0;k<nLinks;k++) {

      unsigned int dst;
      float prob, flow;
      
      linkFile.read((char*)&dst, sizeof(dst));
      linkFile.read((char*)&prob, sizeof(prob));
      linkFile.read((char*)&flow, sizeof(flow));

      int dst_vol = std::floor(dst / 1000);
      int src_vol = std::floor(src / 1000);

      //Only keep what would be used for seeding, and drop low probability transitions
      if(prob < threshold || dst_vol < 7 || dst_vol > 9 || src_vol < 7 || src_vol > 9) continue;

      if(link_map.find(dst) == link_map.end())
      {
        std::vector<unsigned int> invec  = {src};
        std::vector<unsigned int> outvec; 
        link_map[dst] =  {invec,outvec};
      }
      else
      {
        std::map<unsigned int, std::pair<std::vector<unsigned int>,std::vector<unsigned int> > >::iterator it = link_map.find(dst);
        auto linkpair = (it->second);
        auto invec = linkpair.first;
        invec.push_back(src);
      }

      if(link_map.find(src) == link_map.end())
      {
        std::vector<unsigned int> invec;
        std::vector<unsigned int> outvec = {dst}; 
        link_map[src] =  {invec,outvec};
      }
      else
      {
        std::map<unsigned int, std::pair<std::vector<unsigned int>,std::vector<unsigned int> > >::iterator it = link_map.find(src);
        auto linkpair = (it->second);
        auto outvec = linkpair.second;
        outvec.push_back(dst);
      }
      

      //m_links.push_back(LAYER_LINK(linkIndex++,src, dst, prob, flow));
      //std::cout<<"Source "<<src<<" Dest "<<dst<<std::endl;
    }
  }

  linkFile.close();
  };
  ~LayerLinker() {};

  //void getLongStrips(int, std::vector<int>&);

  std::map<unsigned int, std::pair<std::vector<unsigned int>,std::vector<unsigned int> > > link_map;
  //std::vector<LAYER_LINK> m_links;

} LAYER_LINKER;

#endif
