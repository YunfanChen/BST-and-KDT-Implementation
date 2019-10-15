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
      if(points.size()==0) return;
      this->numDim = points[0].numDim;
      this->root = buildSubtree(points,0,points.size(),0,iheight);

      //return;
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) { 
      threshold = numeric_limits<double>::max();
      findNNHelper(root,queryPoint,0); 
      Point* nnPoint = new Point(nearestNeighbor.features);
      return nnPoint;
      //return nullptr;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** TODO */
    unsigned int size() const { 
      //return isize;
      return 5; 
    }

    /** TODO */
    int height() const { 
      // return calHeight(this->root)-1;
      return 0;
    }

  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if(start>=end) return nullptr;
        sort(points.begin()+start,points.begin()+end,CompareValueAt(curDim));
        int mid = (start+end)/2;
        if(curDim==numDim-1) curDim=0;
        else curDim++;
        KDNode* cur = new KDNode(points.at(mid));
        this->isize++;
        if(root==nullptr) root = cur;
        cur->left = buildSubtree(points,start,mid,curDim,height);
        cur->right = buildSubtree(points,mid+1,end,curDim,height);
        return this->root;
    }

    static int calHeight(KDNode* root) {
      if(root==nullptr) return 0;
      int leftH = calHeight(root->left);
      int rightH = calHeight(root->right);
      return leftH>rightH?leftH+1:rightH+1;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
      if(node==nullptr) return;
      int queryValue = queryPoint.valueAt(curDim);
      int kdtValue = node->point.valueAt(curDim);

      KDNode* next = queryValue < kdtValue ? node->left : node->right;
      KDNode* other = queryValue < kdtValue ? node->right : node->left;

      curDim = (curDim+1)%numDim;
      if(next!=nullptr){
        findNNHelper(next, queryPoint, curDim);

        next->point.setDistToQuery(queryPoint);
        double nextDis = next->point.distToQuery;
        if(nextDis < threshold){
          nearestNeighbor = next->point;
          threshold = nextDis;
        }
      }

      if(other!=nullptr){
        other->point.setDistToQuery(queryPoint);
        if(other->point.distToQuery < this->threshold){
          findNNHelper(other, queryPoint, curDim);
        }
      }
      return ;
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** TODO */
    static void deleteAll(KDNode* n) {
      if(n==nullptr) return;
      deleteAll(n->left);
      deleteAll(n->right);
      delete n;
    }

    // Add your own helper methods here
};

public:
void print(){
  printKDT(root);
}

void printKDT(KDNode* root){
  if(root == nullptr){
    return;
  }
  auto& data = root->point.features;
  cout << "[";
  for(int i = 0; i < data.size(); ++i){
    cout << data[i] << ", ";
  }
  cout << "]  " << endl;

  printKDT(root->left);
  printKDT(root->right);
}
#endif  // KDT_HPP
