// GSLAM - A general SLAM framework and benchmark
// Copyright 2018 PILAB Inc. All rights reserved.
// https://github.com/zdzhaoyong/GSLAM
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of Google Inc. nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: zd5945@126.com (Yong Zhao)
//
// Vocabulary is an accelerated version of DBoW: https://github.com/rmsalinas/DBow3

#ifndef GSLAM_VOCABULARY_H
#define GSLAM_VOCABULARY_H

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <map>
#include <vector>
#include <cfloat>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <numeric>      // std::accumulate
#include <chrono>
#include <fstream>
#include <bitset>
#include <memory>

#ifdef __x86_64__
#include <xmmintrin.h>
#include <emmintrin.h>
#endif

#include "GSLAM/core/GImage.h"
#include "GSLAM/core/Messenger.h"

#define GSLAM_VOCABULARY_KMAX 10

namespace GSLAM {

typedef size_t                 NodeId;
typedef size_t                 WordId;
typedef float                  WordValue;
typedef std::map<WordId,float> BowVector;
typedef std::map<WordId,std::vector<unsigned int> > FeatureVector;


typedef GImage TinyMat;

class GeneralScoring;
class Vocabulary
{
public:
    friend class GBoW;


    /// L-norms for normalization
    enum LNorm
    {
      L1,
      L2
    };

    /// Weighting type
    enum WeightingType
    {
      TF_IDF,
      TF,
      IDF,
      BINARY
    };

    /// Scoring type
    enum ScoringType
    {
      L1_NORM,
      L2_NORM,
      CHI_SQUARE,
      KL,
      BHATTACHARYYA,
      DOT_PRODUCT
    };


    /**
     * Initiates an empty vocabulary
     * @param k branching factor
     * @param L depth levels
     * @param weighting weighting type
     * @param scoring scoring type
     */
    Vocabulary(int k = 10, int L = 5,
      WeightingType weighting = TF_IDF, ScoringType scoring = L1_NORM);

    /**
     * Creates the vocabulary by loading a file
     * @param filename
     */
    Vocabulary(const std::string &filename);

    /**
     * Creates a vocabulary from the training features, setting the branching
     * factor nad the depth levels of the tree, and the weighting and scoring
     * schemes
     */
    static std::shared_ptr<Vocabulary> create(const std::vector<TinyMat> &training_features,
       int k = 10, int L = 5,WeightingType weighting = TF_IDF, ScoringType scoring = L1_NORM);

    /**
     * Saves the vocabulary into a file. If filename extension contains .yml, opencv YALM format is used. Otherwise, binary format is employed
     * @param filename
     */
    bool save(const std::string &filename, bool binary_compressed=false) const;

    /**
     * Loads the vocabulary from a file created with save
     * @param filename.
     */
    bool load(const std::string &filename);


    bool load(std::istream& ifs);

    /**
     * Returns the number of nodes in the vocabulary
     * @return number of nodes
     */
    virtual inline unsigned int size() const{
        unsigned int count=0;
        for(auto& n:m_nodes) if(!n.childNum) count++;
        return count;
    }


    /**
     * Returns whether the vocabulary is empty (i.e. it has not been trained)
     * @return true iff the vocabulary is empty
     */
    virtual inline bool empty() const{ return m_nodes.empty();}

    /** Clears the vocabulary object
     */
    void clear();

    void transform(const std::vector<TinyMat>& features, BowVector &v)const;
    /**
     * Transforms a set of descriptores into a bow vector
     * @param features, one per row
     * @param v (out) bow vector of weighted words
     */
    virtual void transform(const  TinyMat & features, BowVector &v)
      const;
    /**
     * Transform a set of descriptors into a bow vector and a feature vector
     * @param features
     * @param v (out) bow vector
     * @param fv (out) feature vector of nodes and feature indexes
     * @param levelsup levels to go up the vocabulary tree to get the node index
     */
    virtual void transform(const std::vector<TinyMat>& features,
      BowVector &v, FeatureVector &fv, int levelsup=0) const;
    /**
     * Transform a set of descriptors into a bow vector and a feature vector
     * @param features
     * @param v (out) bow vector
     * @param fv (out) feature vector of nodes and feature indexes
     * @param levelsup levels to go up the vocabulary tree to get the node index
     */
    virtual void transform(const TinyMat& features,
      BowVector &v, FeatureVector &fv, int levelsup=0) const;

    /**
     * Transforms a single feature into a word (without weight)
     * @param feature
     * @return word id
     */
    virtual WordId transform(const TinyMat& feature) const;

    /**
     * Returns the score of two vectors
     * @param a vector
     * @param b vector
     * @return score between vectors
     * @note the vectors must be already sorted and normalized if necessary
     */
    inline double score(const BowVector &a, const BowVector &b) const;

    /**
     * Returns the id of the node that is "levelsup" levels from the word given
     * @param wid word id
     * @param levelsup 0..L
     * @return node id. if levelsup is 0, returns the node id associated to the
     *   word id
     */
    virtual NodeId getParentNode(WordId wid, int levelsup) const;

    /**
     * Returns the ids of all the words that are under the given node id,
     * by traversing any of the branches that goes down from the node
     * @param nid starting node id
     * @param words ids of words
     */
    void getWordsFromNode(NodeId nid, std::vector<WordId> &words) const;

    /**
     * Returns the branching factor of the tree (k)
     * @return k
     */
    inline int getBranchingFactor() const { return m_k; }

    /**
     * Returns the depth levels of the tree (L)
     * @return L
     */
    inline int getDepthLevels() const { return m_L; }

    /**
     * Returns the real depth levels of the tree on average
     * @return average of depth levels of leaves
     */
    float getEffectiveLevels() const;

    /**
     * Returns the descriptor of a word
     * @param wid word id
     * @return descriptor
     */
    virtual inline TinyMat getWord(WordId wid) const;

    /**
     * Returns the weight of a word
     * @param wid word id
     * @return weight
     */
    virtual inline WordValue getWordWeight(WordId wid) const;

    /**
     * Returns the weighting method
     * @return weighting method
     */
    inline WeightingType getWeightingType() const { return m_weighting; }

    /**
     * Returns the scoring method
     * @return scoring method
     */
    inline ScoringType getScoringType() const { return m_scoring; }

    /**
     * Changes the weighting method
     * @param type new weighting type
     */
    inline void setWeightingType(WeightingType type);

    /**
     * Changes the scoring method
     * @param type new scoring type
     */
    void setScoringType(ScoringType type);


    /**
     * Stops those words whose weight is below minWeight.
     * Words are stopped by setting their weight to 0. There are not returned
     * later when transforming image features into vectors.
     * Note that when using IDF or TF_IDF, the weight is the idf part, which
     * is equivalent to -log(f), where f is the frequency of the word
     * (f = Ni/N, Ni: number of training images where the word is present,
     * N: number of training images).
     * Note that the old weight is forgotten, and subsequent calls to this
     * function with a lower minWeight have no effect.
     * @return number of words stopped now
     */
    virtual int stopWords(double minWeight);


    /** Returns the size of the descriptor employed. If the Vocabulary is empty, returns -1
     */
    int getDescritorSize()const{
        return m_nodeDescriptors.cols;
    }
    /** Returns the type of the descriptor employed normally(8U_C1, 32F_C1)
     */
    int getDescritorType()const{
        return m_nodeDescriptors.type();
    }

    /**
     * Calculates the mean value of a set of descriptors
     * @param descriptors
     * @param mean mean descriptor
     */
     static void meanValue(const std::vector<TinyMat> &descriptors,
      TinyMat &mean)  ;

    /**
     * Calculates the distance between two descriptors
     * @param a
     * @param b
     * @return distance
     */
     float distance(const TinyMat &a, const TinyMat &b)const;


  /**
   * Creates an instance of the scoring object accoring to m_scoring
   */
  void createScoringObject();

  /**
   * Returns the word id associated to a feature
   * @param feature
   * @param id (out) word id
   * @param weight (out) word weight
   * @param nid (out) if given, id of the node "levelsup" levels up
   * @param levelsup
   */
  virtual void transform(const TinyMat &feature,
    WordId &id, WordValue &weight, NodeId* nid, int levelsup = 0) const;
  /**
   * Returns the word id associated to a feature
   * @param feature
   * @param id (out) word id
   * @param weight (out) word weight
   * @param nid (out) if given, id of the node "levelsup" levels up
   * @param levelsup
   */
  virtual void transform(const TinyMat &feature,
    WordId &id, WordValue &weight ) const;

  /**
   * Returns the word id associated to a feature
   * @param feature
   * @param id (out) word id
   */
//  virtual void transform(const TinyMat &feature, WordId &id) const;

  static  void addWeight(BowVector& bow,WordId id, WordValue v)
  {
      BowVector::iterator vit = bow.lower_bound(id);

      if(vit != bow.end() && !(bow.key_comp()(id, vit->first)))
      {
        vit->second += v;
      }
      else
      {
        bow.insert(vit, BowVector::value_type(id, v));
      }
  }

  static void addIfNotExist(BowVector& bow,WordId id, WordValue v)
  {
      BowVector::iterator vit = bow.lower_bound(id);

      if(vit == bow.end() || (bow.key_comp()(id, vit->first)))
      {
        bow.insert(vit, BowVector::value_type(id, v));
      }

  }

  static void normalize(BowVector& bow,LNorm norm_type)
  {
      double norm = 0.0;
      BowVector::iterator it;

      if(norm_type == L1)
      {
        for(it = bow.begin(); it != bow.end(); ++it)
          norm += fabs(it->second);
      }
      else
      {
        for(it = bow.begin(); it != bow.end(); ++it)
          norm += it->second * it->second;
                    norm = sqrt(norm);
      }

      if(norm > 0.0)
      {
        for(it = bow.begin(); it != bow.end(); ++it)
          it->second /= norm;
      }
  }

  static void addFeature(FeatureVector& fvec,NodeId id, unsigned int i_feature)
  {
      FeatureVector::iterator vit = fvec.lower_bound(id);

      if(vit != fvec.end() && vit->first == id)
      {
        vit->second.push_back(i_feature);
      }
      else
      {
        vit = fvec.insert(vit, FeatureVector::value_type(id,
          std::vector<unsigned int>() ));
        vit->second.push_back(i_feature);
      }
  }

  /**
   * Creates a level in the tree, under the parent, by running kmeans with
   * a descriptor set, and recursively creates the subsequent levels too
   * @param parent_id id of parent node
   * @param descriptors descriptors to run the kmeans on
   * @param current_level current level in the tree
   */
  void HKmeansStep(NodeId parent_id, const std::vector<TinyMat> &descriptors,
    int current_level);

//  void unifyDescriptors()
//  {
//      if(!m_nodeDescriptors.empty()) return ;
//      if(!m_nodes.size()) return;
//      int featureBytes=0;
//      for(int i=0;i<m_nodes.size();i++)
//      {
//          Node& node=m_nodes[i];
//          if(node.descriptor.empty()) continue;
//          if(m_nodeDescriptors.empty())
//          {
//              m_nodeDescriptors=TinyMat(m_nodes.size(),node.descriptor.cols,
//                                        node.descriptor.type());
//              featureBytes=m_nodeDescriptors.elemSize()*m_nodeDescriptors.cols;
//          }
//          uchar* dest=m_nodeDescriptors.data+featureBytes*i;
//          memcpy(dest,node.descriptor.data,featureBytes);
//          node.descriptor=TinyMat(1,node.descriptor.cols,node.descriptor.type(),dest);
//      }
//  }

  /// Tree node
  struct Node
  {
      uint32_t     childNum;
      WordValue    weight;

      /**
       * Empty constructor
       */
      Node(): childNum(0), weight(0){}

      /**
       * Returns whether the node is a leaf node
       * @return true iff the node is a leaf
       */
      inline bool isLeaf() const { return childNum==0; }

      void addChild(NodeId _id)
      {
          childNum++;
      }
  };


  struct DistanceFactory
  {
      typedef std::function<float(const uchar*,const uchar*)> DistanceFunc;

      static float hamming32(const uchar* a,const uchar* b)
      {
          const uint64_t *pa = (uint64_t*)a;
          const uint64_t *pb = (uint64_t*)b;
          return std::bitset<64>(pa[0]^pb[0]).count()+std::bitset<64>(pa[1]^pb[1]).count()
                  +std::bitset<64>(pa[2]^pb[2]).count()+std::bitset<64>(pa[3]^pb[3]).count();
      }

      static float hamming64(const uchar* a,const uchar* b){
          const uint64_t *pa = (uint64_t*)a;
          const uint64_t *pb = (uint64_t*)b;
          return std::bitset<64>(pa[0]^pb[0]).count()+std::bitset<64>(pa[1]^pb[1]).count()
                  +std::bitset<64>(pa[2]^pb[2]).count()+std::bitset<64>(pa[3]^pb[3]).count()
                  +std::bitset<64>(pa[4]^pb[4]).count()+std::bitset<64>(pa[5]^pb[5]).count()
                  +std::bitset<64>(pa[6]^pb[6]).count()+std::bitset<64>(pa[7]^pb[7]).count();
      }

      static float hamming8x(const uchar* a,const uchar* b,int bytes)
      {
          const uint64_t *pa = (uint64_t*)a;
          const uint64_t *pb = (uint64_t*)b;

          uint64_t ret = 0;
          for(size_t i = 0; i < bytes / sizeof(uint64_t); ++i, ++pa, ++pb)
          {
              ret+=std::bitset<64>(*pa ^ *pb).count();
          }
          return ret;
      }

#if defined(__AVX2__)
      static float l2avx(const uchar* a,const uchar* b,int floats){
          int _nwords=floats/8;
          __m256 sum=_mm256_setzero_ps(), sub_mult;
          __m256* aptr=(__m256*)a;
          __m256* bptr=(__m256*)b;
         for(int i=0;i<_nwords;i++){
             sub_mult=_mm256_sub_ps(aptr[i],bptr[i]);
             sub_mult=_mm256_mul_ps(sub_mult,sub_mult);
             sum=_mm256_add_ps(sum,sub_mult);
         }
         sum=_mm256_hadd_ps(sum,sum);
         sum=_mm256_hadd_ps(sum,sum);
         float *sum_ptr=(float*)&sum;
         return  sum_ptr[0]+sum_ptr[4];
      }
#endif

#if defined(__SSE2__)&&defined(__SSE__)
      static float l2sse(const uchar* a,const uchar* b,int floats){
          int _nwords=floats/4;
          __m128 sum=_mm_setzero_ps(), sub_mult;
          float* sum_ptr=(float*)&sum;
         //substract, multiply and accumulate
         __m128* aptr=(__m128*)a;
         __m128* bptr=(__m128*)b;
         for(int i=0;i<_nwords;i++){
             sub_mult=_mm_sub_ps(aptr[i],bptr[i]);
             sub_mult=_mm_mul_ps(sub_mult,sub_mult);
             sum=_mm_add_ps(sum,sub_mult);
         }
         return sum_ptr[0]+sum_ptr[1]+sum_ptr[2]+sum_ptr[3] ;
      }
#endif

      static float l2generic(const uchar* a,const uchar* b,int floats){
          float sqd = 0.,tmp;
          const float *a_ptr=(float*)a;
          const float *b_ptr=(float*)b;
          for(int i = 0; i < floats; i ++)
          {
              tmp = (a_ptr[i  ] - b_ptr[i  ]);
              sqd += tmp*tmp;
          }
          return sqd;
      }

      static DistanceFunc create(const TinyMat& des){
          //binary descriptor
          if (des.type()==GImageType<uchar>::Type){
               if(des.cols==32) return std::bind(&DistanceFactory::hamming32,std::placeholders::_1,std::placeholders::_2);
               else if(des.cols==64) return std::bind(&DistanceFactory::hamming64,std::placeholders::_1,std::placeholders::_2);
               else if(des.cols%8==0) return std::bind(&DistanceFactory::hamming8x,std::placeholders::_1,std::placeholders::_2,des.cols);
               else return nullptr;
          }
          else if(des.type()==GImageType<float>::Type){
#if defined(__AVX2__)
               if(des.cols%8) return std::bind(&DistanceFactory::l2avx,std::placeholders::_1,std::placeholders::_2,des.cols);
#endif
#if defined(__SSE2__)
               if(des.cols%4) return std::bind(&DistanceFactory::l2sse,std::placeholders::_1,std::placeholders::_2,des.cols);
#endif
               return std::bind(&DistanceFactory::l2generic,std::placeholders::_1,std::placeholders::_2,des.cols);
          }
          else return nullptr;
      }

  };
public:
    /// Branching factor
    int m_k;

    /// Depth levels
    int m_L;

    /// Weighting method
    WeightingType m_weighting;

    /// Scoring method
    ScoringType m_scoring;

    /// Object for computing scores
    std::shared_ptr<GeneralScoring> m_scoring_object;

    /// Tree nodes
    std::vector<Node> m_nodes;
    TinyMat           m_nodeDescriptors;

private:
    std::shared_ptr<msg::ThreadPool>  m_workthreads;
    DistanceFactory::DistanceFunc   m_distanceFunc;

    /// Words of the vocabulary (tree leaves)
    /// this condition holds: m_words[wid]->word_id == wid
//    std::vector<Node*> m_words;
};
/// Base class of scoring functions
class GeneralScoring
{
public:
  /**
   * Computes the score between two vectors. Vectors must be sorted and
   * normalized if necessary
   * @param v (in/out)
   * @param w (in/out)
   * @return score
   */
  virtual double score(const BowVector &v, const BowVector &w) const = 0;

  /**
   * Returns whether a vector must be normalized before scoring according
   * to the scoring scheme
   * @param norm norm to use
   * @return true iff must normalize
   */
  virtual bool mustNormalize(Vocabulary::LNorm &norm) const = 0;

  static inline const double LOG_EPS(){
      static const double logeps=log(DBL_EPSILON);
      return logeps;
  }

  virtual ~GeneralScoring() {} //!< Required for virtual base classes

};

/**
 * Macro for defining Scoring classes
 * @param NAME name of class
 * @param MUSTNORMALIZE if vectors must be normalized to compute the score
 * @param NORM type of norm to use when MUSTNORMALIZE
 */
#define __SCORING_CLASS(NAME, MUSTNORMALIZE, NORM) \
  NAME: public GeneralScoring \
  { public: \
    /** \
     * Computes score between two vectors \
     * @param v \
     * @param w \
     * @return score between v and w \
     */ \
    virtual double score(const BowVector &v, const BowVector &w) const; \
    \
    /** \
     * Says if a vector must be normalized according to the scoring function \
     * @param norm (out) if true, norm to use
     * @return true iff vectors must be normalized \
     */ \
    virtual inline bool mustNormalize(Vocabulary::LNorm &norm) const  \
      { norm = NORM; return MUSTNORMALIZE; } \
  }

/// L1 Scoring object
class __SCORING_CLASS(L1Scoring, true, Vocabulary::L1);

/// L2 Scoring object
class __SCORING_CLASS(L2Scoring, true, Vocabulary::L2);

/// Chi square Scoring object
class __SCORING_CLASS(ChiSquareScoring, true, Vocabulary::L1);

/// KL divergence Scoring object
class __SCORING_CLASS(KLScoring, true, Vocabulary::L1);

/// Bhattacharyya Scoring object
class __SCORING_CLASS(BhattacharyyaScoring, true, Vocabulary::L1);

/// Dot product Scoring object
class __SCORING_CLASS(DotProductScoring, false, Vocabulary::L1);

#undef __SCORING_CLASS


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double L1Scoring::score(const BowVector &v1, const BowVector &v2) const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      score += fabs(vi - wi) - fabs(vi) - fabs(wi);

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      v1_it = v1.lower_bound(v2_it->first);
      // v1_it = (first element >= v2_it.id)
    }
    else
    {
      // move v2 forward
      v2_it = v2.lower_bound(v1_it->first);
      // v2_it = (first element >= v1_it.id)
    }
  }

  // ||v - w||_{L1} = 2 + Sum(|v_i - w_i| - |v_i| - |w_i|)
  //		for all i | v_i != 0 and w_i != 0
  // (Nister, 2006)
  // scaled_||v - w||_{L1} = 1 - 0.5 * ||v - w||_{L1}
  score = -score/2.0;

  return score; // [0..1]
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double L2Scoring::score(const BowVector &v1, const BowVector &v2) const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      score += vi * wi;

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      v1_it = v1.lower_bound(v2_it->first);
      // v1_it = (first element >= v2_it.id)
    }
    else
    {
      // move v2 forward
      v2_it = v2.lower_bound(v1_it->first);
      // v2_it = (first element >= v1_it.id)
    }
  }

  // ||v - w||_{L2} = sqrt( 2 - 2 * Sum(v_i * w_i) )
        //		for all i | v_i != 0 and w_i != 0 )
        // (Nister, 2006)
        if(score >= 1) // rounding errors
          score = 1.0;
        else
    score = 1.0 - sqrt(1.0 - score); // [0..1]

  return score;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double ChiSquareScoring::score(const BowVector &v1, const BowVector &v2)
  const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  // all the items are taken into account

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      // (v-w)^2/(v+w) - v - w = -4 vw/(v+w)
      // we move the -4 out
      if(vi + wi != 0.0) score += vi * wi / (vi + wi);

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      v1_it = v1.lower_bound(v2_it->first);
    }
    else
    {
      // move v2 forward
      v2_it = v2.lower_bound(v1_it->first);
    }
  }

  // this takes the -4 into account
  score = 2. * score; // [0..1]

  return score;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double KLScoring::score(const BowVector &v1, const BowVector &v2) const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  // all the items or v are taken into account

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      if(vi != 0 && wi != 0) score += vi * log(vi/wi);

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      score += vi * (log(vi) - LOG_EPS());
      ++v1_it;
    }
    else
    {
      // move v2_it forward, do not add any score
      v2_it = v2.lower_bound(v1_it->first);
      // v2_it = (first element >= v1_it.id)
    }
  }

  // sum rest of items of v
  for(; v1_it != v1_end; ++v1_it)
    if(v1_it->second != 0)
      score += v1_it->second * (log(v1_it->second) - LOG_EPS());

  return score; // cannot be scaled
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double BhattacharyyaScoring::score(const BowVector &v1,
  const BowVector &v2) const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      score += sqrt(vi * wi);

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      v1_it = v1.lower_bound(v2_it->first);
      // v1_it = (first element >= v2_it.id)
    }
    else
    {
      // move v2 forward
      v2_it = v2.lower_bound(v1_it->first);
      // v2_it = (first element >= v1_it.id)
    }
  }

  return score; // already scaled
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

inline double DotProductScoring::score(const BowVector &v1,
  const BowVector &v2) const
{
  BowVector::const_iterator v1_it, v2_it;
  const BowVector::const_iterator v1_end = v1.end();
  const BowVector::const_iterator v2_end = v2.end();

  v1_it = v1.begin();
  v2_it = v2.begin();

  double score = 0;

  while(v1_it != v1_end && v2_it != v2_end)
  {
    const WordValue& vi = v1_it->second;
    const WordValue& wi = v2_it->second;

    if(v1_it->first == v2_it->first)
    {
      score += vi * wi;

      // move v1 and v2 forward
      ++v1_it;
      ++v2_it;
    }
    else if(v1_it->first < v2_it->first)
    {
      // move v1 forward
      v1_it = v1.lower_bound(v2_it->first);
      // v1_it = (first element >= v2_it.id)
    }
    else
    {
      // move v2 forward
      v2_it = v2.lower_bound(v1_it->first);
      // v2_it = (first element >= v1_it.id)
    }
  }

  return score; // cannot scale
}

inline Vocabulary::Vocabulary
  (int k, int L, WeightingType weighting, ScoringType scoring)
  : m_k(k), m_L(L), m_weighting(weighting), m_scoring(scoring),m_distanceFunc(nullptr)
{
  createScoringObject();
}

// --------------------------------------------------------------------------


inline Vocabulary::Vocabulary
  (const std::string &filename): m_scoring_object(NULL),m_distanceFunc(nullptr)
{
  load(filename);
}

// --------------------------------------------------------------------------


inline void Vocabulary::createScoringObject()
{
  m_scoring_object.reset();

  switch(m_scoring)
  {
    case L1_NORM:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new L1Scoring);
      break;

    case L2_NORM:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new L2Scoring);
      break;

    case CHI_SQUARE:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new ChiSquareScoring);
      break;

    case KL:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new KLScoring);
      break;

    case BHATTACHARYYA:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new BhattacharyyaScoring);
      break;

    case DOT_PRODUCT:
      m_scoring_object = std::shared_ptr<GeneralScoring>(new DotProductScoring);
      break;

  }
}

// --------------------------------------------------------------------------


inline void Vocabulary::setScoringType(ScoringType type)
{
  m_scoring = type;
  createScoringObject();
}

// --------------------------------------------------------------------------


inline void Vocabulary::setWeightingType(WeightingType type)
{
  this->m_weighting = type;
}

inline std::shared_ptr<Vocabulary> Vocabulary::create(const std::vector<TinyMat> &imgFeatures,
                        int k , int L,WeightingType weighting , ScoringType scoring)
{
    std::shared_ptr<Vocabulary> voc(new Vocabulary(k,L,weighting,scoring));

    // expected_nodes = Sum_{i=0..L} ( k^i )
    int expected_nodes =(int)((pow((double)voc->m_k, (double)voc->m_L + 1) - 1)/(voc->m_k - 1));
    TinyMat firstF=imgFeatures.front();
    voc->m_nodes.resize(expected_nodes);
    voc->m_nodeDescriptors=TinyMat(expected_nodes,firstF.cols,firstF.type(),nullptr,false,32);
    int featBytes=firstF.elemSize()*firstF.cols;

    if(!voc->m_distanceFunc) voc->m_distanceFunc=DistanceFactory::create(firstF);

    // create the tree
    int featureNum=0;
    for(const TinyMat& m:imgFeatures)
        featureNum+=m.rows;
    TinyMat featureHolder(featureNum,firstF.cols,firstF.type(),nullptr,false,32);
    LOG_IF(INFO,(((int64_t)featureHolder.data)&0x1F)!=0)
            <<"FeatureHolder adress "<<((int64_t)featureHolder.data)
           <<" are not ready to perform AVX acceleration.\n";
    std::vector<TinyMat> vtf;
    vtf.reserve(featureNum);
    for(const TinyMat& m:imgFeatures){
        auto curSize=vtf.size();
        memcpy(featureHolder.data+featBytes*curSize,m.data,featBytes*m.rows);
        for(int iend=curSize+m.rows;curSize<iend;curSize++)
            vtf.push_back(featureHolder.row(curSize));
    }

    voc->m_workthreads=std::shared_ptr<msg::ThreadPool>(new msg::ThreadPool(k));
    voc->HKmeansStep(0, vtf, 1);

    // and set the weight of each node of the tree
    const unsigned int NWords = voc->m_nodes.size();
    const unsigned int NDocs = imgFeatures.size();

    if(voc->m_weighting == TF || voc->m_weighting == BINARY)
    {
      // idf part must be 1 always
      for(unsigned int i = 0; i < NWords; i++)
        voc->m_nodes[i].weight = 1;
    }
    else if(voc->m_weighting == IDF || voc->m_weighting == TF_IDF)
    {
      // IDF and TF-IDF: we calculte the idf path now

      // Note: this actually calculates the idf part of the tf-idf score.
      // The complete tf-idf score is calculated in ::transform

      std::vector<unsigned int> Ni(NWords, 0);
      std::vector<bool> counted(NWords, false);


      for(const TinyMat& mit:imgFeatures)
      {
        fill(counted.begin(), counted.end(), false);
        for(int r=0;r<mit.rows;r++)
        {
          WordId word_id;
          WordValue weight;
          voc->transform(mit.row(r), word_id,weight);

          if(!counted[word_id])
          {
            Ni[word_id]++;
            counted[word_id] = true;
          }
        }
      }

      // set ln(N/Ni)
      for(unsigned int i = 0; i < NWords; i++)
      {
        if(Ni[i] > 0)
        {
          voc->m_nodes[i].weight = log((double)NDocs / (double)Ni[i]);
        }// else // This cannot occur if using kmeans++
      }
    }

//    voc->unifyDescriptors();
    return voc;

}
// --------------------------------------------------------------------------

inline void Vocabulary::HKmeansStep(NodeId parent_id,
                             const std::vector<TinyMat> &descriptors, int current_level)
{

    if(descriptors.empty()) return;
    // features associated to each cluster
    std::vector<TinyMat> clusters;
    std::vector<std::vector<unsigned int> > groups; // groups[i] = [j1, j2, ...]
    // j1, j2, ... indices of descriptors associated to cluster i

    clusters.reserve(m_k);
    groups.reserve(m_k);


    if((int)descriptors.size() <= m_k)
    {
        // trivial case: one cluster per feature
        groups.resize(descriptors.size());

        for(unsigned int i = 0; i < descriptors.size(); i++)
        {
            groups[i].push_back(i);
            clusters.push_back(descriptors[i]);
        }
    }
    else
    {
        // select clusters and groups with kmeans

        bool first_time = true;
        bool goon = true;

        // to check if clusters move after iterations
        std::vector<int> last_association, current_association;

        while(goon)
        {
            // 1. Calculate clusters

            if(first_time)
            {
                // random sample
//                initiateClusters(descriptors, clusters);
                // Implements kmeans++ seeding algorithm
                // Algorithm:
                // 1. Choose one center uniformly at random from among the data points.
                // 2. For each data point x, compute D(x), the distance between x and the nearest
                //    center that has already been chosen.
                // 3. Add one new data point as a center. Each point x is chosen with probability
                //    proportional to D(x)^2.
                // 4. Repeat Steps 2 and 3 until k centers have been chosen.
                // 5. Now that the initial centers have been chosen, proceed using standard k-means
                //    clustering.


              //  DUtils::Random::SeedRandOnce();

                clusters.resize(0);
                clusters.reserve(m_k);
                std::vector<double> min_dists(descriptors.size(), std::numeric_limits<double>::max());

                // 1.

                int ifeature = rand()% descriptors.size();//DUtils::Random::RandomInt(0, pfeatures.size()-1);

                // create first cluster
                clusters.push_back(descriptors[ifeature]);

                // compute the initial distances
                 std::vector<double>::iterator dit;
                dit = min_dists.begin();
                for(auto fit = descriptors.begin(); fit != descriptors.end(); ++fit, ++dit)
                {
                  *dit = distance((*fit), clusters.back());
                }

                while((int)clusters.size() < m_k)
                {
                  // 2.
                  dit = min_dists.begin();
                  for(auto  fit = descriptors.begin(); fit != descriptors.end(); ++fit, ++dit)
                  {
                    if(*dit > 0)
                    {
                      double dist = distance((*fit), clusters.back());
                      if(dist < *dit) *dit = dist;
                    }
                  }

                  // 3.
                  double dist_sum = std::accumulate(min_dists.begin(), min_dists.end(), 0.0);

                  if(dist_sum > 0)
                  {
                    double cut_d;
                    do
                    {

                      cut_d = (double(rand())/ double(RAND_MAX))* dist_sum;
                    } while(cut_d == 0.0);

                    double d_up_now = 0;
                    for(dit = min_dists.begin(); dit != min_dists.end(); ++dit)
                    {
                      d_up_now += *dit;
                      if(d_up_now >= cut_d) break;
                    }

                    if(dit == min_dists.end())
                      ifeature = descriptors.size()-1;
                    else
                      ifeature = dit - min_dists.begin();


                    clusters.push_back(descriptors[ifeature]);
                  } // if dist_sum > 0
                  else
                    break;

                } // while(used_clusters < m_k)
            }
            else
            {
                // calculate cluster centres

                for(unsigned int c = 0; c < clusters.size(); ++c)
                {
                    std::vector<TinyMat> cluster_descriptors;
                    cluster_descriptors.reserve(groups[c].size());
                    std::vector<unsigned int>::const_iterator vit;
                    for(vit = groups[c].begin(); vit != groups[c].end(); ++vit)
                    {
                        cluster_descriptors.push_back(descriptors[*vit]);
                    }

                    meanValue(cluster_descriptors, clusters[c]);
                }

            } // if(!first_time)

            // 2. Associate features with clusters

            // calculate distances to cluster centers
            groups.clear();
            groups.resize(clusters.size(), std::vector<unsigned int>());
            current_association.resize(descriptors.size());

            //assoc.clear();

            //unsigned int d = 0;
            for(auto  fit = descriptors.begin(); fit != descriptors.end(); ++fit)//, ++d)
            {
                double best_dist = distance((*fit), clusters[0]);
                unsigned int icluster = 0;

                for(unsigned int c = 1; c < clusters.size(); ++c)
                {
                    double dist = distance((*fit), clusters[c]);
                    if(dist < best_dist)
                    {
                        best_dist = dist;
                        icluster = c;
                    }
                }

                //assoc.ref<unsigned char>(icluster, d) = 1;

                groups[icluster].push_back(fit - descriptors.begin());
                current_association[ fit - descriptors.begin() ] = icluster;
            }

            // kmeans++ ensures all the clusters has any feature associated with them

            // 3. check convergence
            if(first_time)
            {
                first_time = false;
            }
            else
            {
                //goon = !eqUChar(last_assoc, assoc);

                goon = false;
                for(unsigned int i = 0; i < current_association.size(); i++)
                {
                    if(current_association[i] != last_association[i]){
                        goon = true;
                        break;
                    }
                }
            }

            if(goon)
            {
                // copy last feature-cluster association
                last_association = current_association;
                //last_assoc = assoc.clone();
            }

        } // while(goon)

    } // if must run kmeans

    // create nodes
    Node& parent=m_nodes[parent_id];
    parent.childNum=clusters.size();
    int des_bytes=m_nodeDescriptors.cols*m_nodeDescriptors.elemSize();
    int childID=parent_id*m_k+1;
    uchar* des_data=m_nodeDescriptors.data+des_bytes*(childID);
    for(unsigned int i = 0; i < clusters.size(); ++i)
    {
        memcpy(des_data,clusters[i].data,des_bytes);
    }

    std::vector<std::future<void> > futures;
    // go on with the next level
    if(current_level < m_L)
    {
        // iterate again with the resulting clusters
        for(unsigned int i = 0; i < parent.childNum; ++i)
        {
            NodeId id = childID+i;

            std::vector<TinyMat> child_features;
            child_features.reserve(groups[i].size());

            std::vector<unsigned int>::const_iterator vit;
            for(vit = groups[i].begin(); vit != groups[i].end(); ++vit)
            {
                child_features.push_back(descriptors[*vit]);
            }

            if(child_features.size() > 1)
            {
                if(m_workthreads&&current_level==1)
                    futures.push_back(m_workthreads->Add([this,id,child_features,current_level](){
                        return HKmeansStep(id, child_features, current_level + 1);
                    }));
                else
                    HKmeansStep(id, child_features, current_level + 1);
            }
        }
    }
    for(auto& f:futures) f.wait();

}


// --------------------------------------------------------------------------

inline float Vocabulary::getEffectiveLevels() const
{
    return 0;
//  long sum = 0;
//   for(auto wit = m_words.begin(); wit != m_words.end(); ++wit)
//  {
//    const Node *p = *wit;

//    for(; p->id != 0; sum++) p = &m_nodes[p->parent];
//  }

//  return (float)((double)sum / (double)m_words.size());
}

// --------------------------------------------------------------------------


inline TinyMat Vocabulary::getWord(WordId wid) const
{
  return m_nodeDescriptors.row(wid);
}

// --------------------------------------------------------------------------


inline WordValue Vocabulary::getWordWeight(WordId wid) const
{
  return m_nodes[wid].weight;
}

// --------------------------------------------------------------------------


inline WordId Vocabulary::transform
  (const TinyMat& feature) const
{
  if(empty())
  {
    return 0;
  }

  WordId wid;
  WordValue weight;
  transform(feature, wid,weight);
  return wid;
}

// --------------------------------------------------------------------------

inline void Vocabulary::transform(
        const TinyMat& features, BowVector &v) const
{
    //    std::vector<TinyMat> vf(features.rows);
    //    for(int r=0;r<features.rows;r++) vf[r]=features.rowRange(r,r+1);
    //    transform(vf,v);



    v.clear();

    if(empty())
    {
        return;
    }

    // normalize
    LNorm norm;
    bool must = m_scoring_object->mustNormalize(norm);


    if(m_weighting == TF || m_weighting == TF_IDF)
    {
        for(int r=0;r<features.rows;r++)
        {
            WordId id;
            WordValue w;
            // w is the idf value if TF_IDF, 1 if TF
            transform(features.row(r), id, w);
            // not stopped
            if(w > 0)  addWeight(v,id, w);
        }

        if(!v.empty() && !must)
        {
            // unnecessary when normalizing
            const double nd = v.size();
            for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
                vit->second /= nd;
        }

    }
    else // IDF || BINARY
    {
        for(int r=0;r<features.rows;r++)
        {
            WordId id;
            WordValue w;
            // w is idf if IDF, or 1 if BINARY

            transform(features.row(r), id, w);

            // not stopped
            if(w > 0) addIfNotExist(v,id, w);

        } // if add_features
    } // if m_weighting == ...

    if(must) normalize(v,norm);

}



inline void Vocabulary::transform(const std::vector<TinyMat>& features, BowVector &v) const
{
  v.clear();

  if(empty())
  {
    return;
  }

  // normalize
  LNorm norm;
  bool must = m_scoring_object->mustNormalize(norm);


  if(m_weighting == TF || m_weighting == TF_IDF)
  {
    for(auto fit = features.begin(); fit < features.end(); ++fit)
    {
      WordId id;
      WordValue w;
      // w is the idf value if TF_IDF, 1 if TF

      transform(*fit, id, w);

      // not stopped
      if(w > 0) addWeight(v,id, w);
    }

    if(!v.empty() && !must)
    {
      // unnecessary when normalizing
      const double nd = v.size();
      for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
        vit->second /= nd;
    }

  }
  else // IDF || BINARY
  {
    for(auto fit = features.begin(); fit < features.end(); ++fit)
    {
      WordId id;
      WordValue w;
      // w is idf if IDF, or 1 if BINARY

      transform(*fit, id, w);

      // not stopped
      if(w > 0) addIfNotExist(v,id, w);

    } // if add_features
  } // if m_weighting == ...

  if(must) normalize(v,norm);
}

// --------------------------------------------------------------------------
inline void Vocabulary::transform(const TinyMat& features,
      BowVector &v, FeatureVector &fv, int levelsup) const
{
    v.clear();
    fv.clear();

    if(empty()) // safe for subclasses
    {
      return;
    }

    // normalize
    LNorm norm;
    bool must = m_scoring_object->mustNormalize(norm);


    if(m_weighting == TF || m_weighting == TF_IDF)
    {
      for(unsigned int i_feature = 0; i_feature<features.rows; ++i_feature)
      {
        WordId id;
        NodeId nid;
        WordValue w;
        // w is the idf value if TF_IDF, 1 if TF

        transform(features.row(i_feature), id, w, &nid, levelsup);

        if(w > 0) // not stopped
        {
          addWeight(v,id, w);
          addFeature(fv,nid, i_feature);
        }
      }

      if(!v.empty() && !must)
      {
        // unnecessary when normalizing
        const double nd = v.size();
        for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
          vit->second /= nd;
      }

    }
    else // IDF || BINARY
    {
        for(unsigned int i_feature = 0; i_feature<features.rows; ++i_feature)
      {
        WordId id;
        NodeId nid;
        WordValue w;
        // w is idf if IDF, or 1 if BINARY

        transform(features.row(i_feature), id, w, &nid, levelsup);

        if(w > 0) // not stopped
        {
          addIfNotExist(v,id, w);
          addFeature(fv,nid, i_feature);
        }
      }
    } // if m_weighting == ...

    if(must) normalize(v,norm);
}

inline void Vocabulary::transform(
  const std::vector<TinyMat>& features,
  BowVector &v, FeatureVector &fv, int levelsup) const
{
  v.clear();
  fv.clear();

  if(empty()) // safe for subclasses
  {
    return;
  }

  // normalize
  LNorm norm;
  bool must = m_scoring_object->mustNormalize(norm);


  if(m_weighting == TF || m_weighting == TF_IDF)
  {
    unsigned int i_feature = 0;
    for(auto fit = features.begin(); fit < features.end(); ++fit, ++i_feature)
    {
      WordId id;
      NodeId nid;
      WordValue w;
      // w is the idf value if TF_IDF, 1 if TF

      transform(*fit, id, w, &nid, levelsup);

      if(w > 0) // not stopped
      {
        addWeight(v,id, w);
        addFeature(fv,nid, i_feature);
      }
    }

    if(!v.empty() && !must)
    {
      // unnecessary when normalizing
      const double nd = v.size();
      for(BowVector::iterator vit = v.begin(); vit != v.end(); vit++)
        vit->second /= nd;
    }

  }
  else // IDF || BINARY
  {
    unsigned int i_feature = 0;
    for(auto fit = features.begin(); fit < features.end(); ++fit, ++i_feature)
    {
      WordId id;
      NodeId nid;
      WordValue w;
      // w is idf if IDF, or 1 if BINARY

      transform(*fit, id, w, &nid, levelsup);

      if(w > 0) // not stopped
      {
        addIfNotExist(v,id, w);
        addFeature(fv,nid, i_feature);
      }
    }
  } // if m_weighting == ...

  if(must) normalize(v,norm);
}


// --------------------------------------------------------------------------


inline void Vocabulary::transform(const TinyMat &feature,
  WordId &word_id, WordValue &weight, NodeId *nid, int levelsup) const
{
  // propagate the feature down the tree


  // level at which the node must be stored in nid, if given
  const int nid_level = m_L - levelsup;
  if(nid_level <= 0 && nid != NULL) *nid = 0; // root

  NodeId final_id = 0; // root
  int current_level = 0;
  int featureBytes=m_nodeDescriptors.cols*m_nodeDescriptors.elemSize();

  do
  {
    ++current_level;
    float best_d = std::numeric_limits<float>::max();
    NodeId best_id= final_id;

    const Node& node=m_nodes[final_id];
    NodeId id=final_id*m_k+1;
    for(NodeId idEnd=id+node.childNum;id<idEnd;++id)
    {
      float d = m_distanceFunc(feature.data, m_nodeDescriptors.data+featureBytes*id);
      if(d < best_d)
      {
        best_d = d;
        best_id = id;
      }
    }
    final_id=best_id;

    if(nid != NULL && current_level == nid_level)
      *nid = final_id;

  } while( !m_nodes[final_id].isLeaf() );

  // turn node id into word id
  word_id = final_id;
  weight = m_nodes[final_id].weight;
}



inline void Vocabulary::transform(const TinyMat &feature,
                           WordId &word_id, WordValue &weight ) const
{
    // propagate the feature down the tree
    // level at which the node must be stored in nid, if given
    NodeId final_id = 0;
    do
    {
        const Node& node = m_nodes[final_id];
        float best_d = std::numeric_limits<float>::max();
        NodeId   bestID=final_id;
        int idx=0;
        for(int i=0;i<node.childNum;i++)
        {
            NodeId id=final_id*m_k+1+i;
            uint64_t dist= distance(feature, m_nodeDescriptors.row(id));
            if(dist < best_d)
            {
                best_d = dist;
                bestID = id;
            }
            idx++;
        }
        final_id=bestID;

    } while( !m_nodes[final_id].isLeaf() );

    // turn node id into word id
    word_id = final_id;//m_nodes[final_id].word_id;
    weight = m_nodes[final_id].weight;
}
// --------------------------------------------------------------------------

inline NodeId Vocabulary::getParentNode
  (WordId wid, int levelsup) const
{
  NodeId ret = wid;//m_words[wid]->id; // node id
  while(levelsup > 0 && ret != 0) // ret == 0 --> root
  {
    --levelsup;
    ret = (ret-1)/m_k;
  }
  return ret;
}

// --------------------------------------------------------------------------


inline void Vocabulary::getWordsFromNode
  (NodeId nid, std::vector<WordId> &words) const
{
  words.clear();

  if(m_nodes[nid].isLeaf())
  {
    words.push_back(nid);
  }
  else
  {
    words.reserve(m_k); // ^1, ^2, ...

    std::vector<NodeId> parents;
    parents.push_back(nid);

    while(!parents.empty())
    {
      NodeId parentid = parents.back();
      parents.pop_back();

      for(int i=0;i<m_nodes[parentid].childNum;i++)
      {
        const auto id=parentid*m_k+1+i;

        if(m_nodes[id].isLeaf())
          words.push_back(id);
        else
          parents.push_back(id);

      } // for each child
    } // while !parents.empty
  }
}

// --------------------------------------------------------------------------


inline int Vocabulary::stopWords(double minWeight)
{
  int c = 0;
   for(auto wit = m_nodes.begin(); wit != m_nodes.end(); ++wit)
  {
    if((*wit).weight < minWeight)
    {
      ++c;
      (*wit).weight = 0;
    }
  }
  return c;
}

// --------------------------------------------------------------------------


inline bool Vocabulary::save(const std::string &filename,  bool compressed) const
{
    if(filename.find(".yml")!=std::string::npos)
    {
        return false;
    }
    compressed=false;

    std::ofstream out_str(filename);
    if (!out_str) throw std::runtime_error("Vocabulary::saveBinary Could not open file :"+filename+" for writing");

    uint64_t sig=88877711233;//magic number describing the file
    out_str.write((char*)&sig,sizeof(sig));
    out_str.write((char*)&compressed,sizeof(compressed));
    uint32_t nnodes=m_nodes.size();
    out_str.write((char*)&nnodes,sizeof(nnodes));
    if (nnodes==0) return false;
    //save everything to a stream
    std::stringstream aux_stream;
    aux_stream.write((char*)&m_k,sizeof(m_k));
    aux_stream.write((char*)&m_L,sizeof(m_L));
    aux_stream.write((char*)&m_scoring,sizeof(m_scoring));
    aux_stream.write((char*)&m_weighting,sizeof(m_weighting));
    int type=getDescritorType();
    int cols=getDescritorSize();
    int rows=1;
    aux_stream.write((char*)&cols,sizeof(cols));
    aux_stream.write((char*)&rows,sizeof(rows));
    aux_stream.write((char*)&type,sizeof(type));

    aux_stream.write((char*)m_nodes.data(),sizeof(Node)*m_nodes.size());
    aux_stream.write((char*)m_nodeDescriptors.data,
                     m_nodeDescriptors.elemSize()*m_nodeDescriptors.total());

    //now, decide if compress or not
    if (compressed){
        return false;
    }
    else{
        out_str<<aux_stream.rdbuf();
    }

    return true;
}

// --------------------------------------------------------------------------

inline bool Vocabulary::load(std::istream& ifile)
{
    uint64_t sig;//magic number describing the file
    ifile.read((char*)&sig,sizeof(sig));
    if (sig==88877711233) {//it is a binary file. read from it
        bool compressed;
        uint32_t nnodes;
        ifile.read((char*)&compressed,sizeof(compressed));
        ifile.read((char*)&nnodes,sizeof(nnodes));
        if(nnodes==0) return false;
        std::istream *_used_str=0;
        if (compressed){
            return false;
        }
        else
        {
            _used_str=&ifile;
        }

        _used_str->read((char*)&m_k,sizeof(m_k));
        _used_str->read((char*)&m_L,sizeof(m_L));
        _used_str->read((char*)&m_scoring,sizeof(m_scoring));
        _used_str->read((char*)&m_weighting,sizeof(m_weighting));

        createScoringObject();

        int type,cols,rows;
        _used_str->read((char*)&cols,sizeof(cols));
        _used_str->read((char*)&rows,sizeof(rows));
        _used_str->read((char*)&type,sizeof(type));
        m_nodes.resize(nnodes);
        m_nodeDescriptors=TinyMat(nnodes,cols,type,nullptr,false,32);
        m_distanceFunc=DistanceFactory::create(m_nodeDescriptors);

        _used_str->read((char*)m_nodes.data(),nnodes*sizeof(Node));
        _used_str->read((char*)m_nodeDescriptors.data,
                        m_nodeDescriptors.total()*m_nodeDescriptors.elemSize());

        return true;
    }
    std::cerr<<"Vocabulary: Wrong signature.";
    return false;
}

inline bool Vocabulary::load(const std::string &filename)
{
    // try binary formats : *.gbow
    {
        std::ifstream ifile(filename,std::ios::in|std::ios::binary);
        if (!ifile.is_open())
        {
            std::cerr<<"Vocabulary::load Could not open file "<<filename<<" for reading"<<std::endl;
            return false;
        }
        return load(ifile);
    }

    // other formats
    if(filename.find(".yml")!=std::string::npos)
    {
        throw std::runtime_error( "Vocabulary loading failure: .yml loading is not implemented!" );
    }
    else if(filename.find(".voc")!=std::string::npos)
    {
        throw std::runtime_error( "Vocabulary loading failure: .voc loading is not implemented!" );
    }
    return false;
}
// --------------------------------------------------------------------------

/**
 * Writes printable information of the vocabulary
 * @param os stream to write to
 * @param voc
 */

inline std::ostream& operator<<(std::ostream &os,
  const Vocabulary &voc)
{
  os << "Vocabulary: k = " << voc.getBranchingFactor()
    << ", L = " << voc.getDepthLevels()
    << ", Weighting = ";

  switch(voc.getWeightingType())
  {
    case Vocabulary::TF_IDF: os << "tf-idf"; break;
    case Vocabulary::TF: os << "tf"; break;
    case Vocabulary::IDF: os << "idf"; break;
    case Vocabulary::BINARY: os << "binary"; break;
  }

  os << ", Scoring = ";
  switch(voc.getScoringType())
  {
    case Vocabulary::L1_NORM: os << "L1-norm"; break;
    case Vocabulary::L2_NORM: os << "L2-norm"; break;
    case Vocabulary::CHI_SQUARE: os << "Chi square distance"; break;
    case Vocabulary::KL: os << "KL-divergence"; break;
    case Vocabulary::BHATTACHARYYA: os << "Bhattacharyya coefficient"; break;
    case Vocabulary::DOT_PRODUCT: os << "Dot product"; break;
  }

  os << ", Number of words = " << voc.size();

  return os;
}


/**
 * @brief Vocabulary::clear
 */
inline void Vocabulary::clear(){
    m_scoring_object.reset();
    m_scoring_object=0;
    m_nodes.clear();
    m_nodeDescriptors=TinyMat();
}

inline void Vocabulary::meanValue(const std::vector<TinyMat> &descriptors,
                       TinyMat &mean)
{

    if(descriptors.empty()) return;

    if(descriptors.size() == 1)
    {
        mean = descriptors[0].clone();
        return;
    }
    //binary descriptor
    if (descriptors[0].type()==GImageType<uchar>::Type ){
        //determine number of bytes of the binary descriptor
        int L= descriptors[0].cols;
        std::vector<int> sum( L * 8, 0);

        for(size_t i = 0; i < descriptors.size(); ++i)
        {
            const TinyMat &d = descriptors[i];
            const unsigned char *p = d.data;

            for(int j = 0; j < d.cols; ++j, ++p)
            {
                if(*p & (1 << 7)) ++sum[ j*8     ];
                if(*p & (1 << 6)) ++sum[ j*8 + 1 ];
                if(*p & (1 << 5)) ++sum[ j*8 + 2 ];
                if(*p & (1 << 4)) ++sum[ j*8 + 3 ];
                if(*p & (1 << 3)) ++sum[ j*8 + 4 ];
                if(*p & (1 << 2)) ++sum[ j*8 + 5 ];
                if(*p & (1 << 1)) ++sum[ j*8 + 6 ];
                if(*p & (1))      ++sum[ j*8 + 7 ];
            }
        }

        mean = TinyMat(1, L, GImageType<uchar>::Type);
        memset(mean.data,0,mean.total());
        unsigned char *p = mean.data;

        const int N2 = (int)descriptors.size() / 2 + descriptors.size() % 2;
        for(size_t i = 0; i < sum.size(); ++i)
        {
            if(sum[i] >= N2)
            {
                // set bit
                *p |= 1 << (7 - (i % 8));
            }

            if(i % 8 == 7) ++p;
        }
    }
    //non binary descriptor
    else{
        assert(descriptors[0].type()==GImageType<float>::Type);//ensure it is float

        mean= TinyMat(1, descriptors[0].cols,GImageType<float>::Type);
        memset(mean.data,0,mean.total()*mean.elemSize());
        float inv_s =1./double( descriptors.size());
        for(size_t i=0;i<descriptors.size();i++)
            for(int idx=0;idx<descriptors[i].total();idx++)
            mean.at<float>(idx) +=  ((float*)descriptors[i].data)[idx] * inv_s;

    }
}

inline float Vocabulary::distance(const TinyMat &a,  const TinyMat &b)const
{
    return m_distanceFunc(a.data,b.data);
}

}


#endif

