#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    /** TODO */
    void build(vector<Point>& points) {
      if(points==nullptr) return;
      this->root = buildSubtree(points,0,points.size(),0,iheight);
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) { 
      findNNHelper(root,queryPoint,0); 
      return nnPoint;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** TODO */
    unsigned int size() const { return 0; }

    /** TODO */
    int height() const { return 0; }

  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if(start>=end) return nullptr;
        sort(points.begin()+start,points.begin()+end-1,CompareValueAt(curDim));
        int mid = (start+end)/2;
        if(curDim==points.begin()->numDim-1) curDim==0;
        else curDim++;
        points.at(mid).left = buildSubtree(points,start,mid,curDim,height);
        points.at(mid).right = buildSubtree(points,mid+1,end,curDim,height);
        return points.at(mid);
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
      if(node==nullptr) return;
      int queryValue = queryPoint.valueAt(curDim);
      int kdtValue = node->point.valueAt(curDim);

      Point* next = queryValue < kdtValue ? node->left : node->right;
      Point* other = queryValue < kdtValue ? node->right : node->left;

      curDim = (curDim+1)%node->numDim;
      findNNHelper(next, queryPoint, curDim);

      next->setDistToQuery(queryPoint);
      double nextDis = next->distToQuery;
      if(this->nearestNeighbor==nullptr){
        this->nearestNeighbor = *next;
        this->threshold = nextDis;
      }else{
        if(nextDis<this->threshold){
          this->nearestNeighbor = next;
          this->threshold = nextDis;
        }
      }
      other->setDistToQuery(queryPoint);
      if(other!=nullptr && other->distToQuery < this->threshold){
        findNNHelper(other, queryPoint, curDim);
      }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    static void deleteAll(KDNode* n) {}

    // Add your own helper methods here
};
#endif  // KDT_HPP
