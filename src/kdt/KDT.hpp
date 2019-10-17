//Yunfan Chen
//A53287711
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

    /** Build the KD Tree */
    void build(vector<Point>& points) {
      if(points.size()==0) return;
      this->numDim = points[0].features.size();
      this->root = buildSubtree(points,0,points.size(),0,iheight);
    }

    /** Find the nearest neighbor of the query point. */
    Point* findNearestNeighbor(Point& queryPoint) { 
      threshold = numeric_limits<double>::max(); // initialize it as max value
      findNNHelper(root,queryPoint,0);  // go to healper function.
      return &nearestNeighbor; // return it as pointer
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** Get the size of KDT. */
    unsigned int size() const { 
      return isize;
    }

    /** Get the height of KDT. */
    int height() const { 
      if(this->root==nullptr) return -1; 
      return calHeight(this->root)-1;
    }

  private:
    /** Helper function to build KDT recursively. */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if(start>=end) return nullptr; // end point
        // sort the feathures orderly, according to the dimension
        sort(points.begin()+start,points.begin()+end,CompareValueAt(curDim)); 
        // Get the frature in the middle
        int mid = (start+end)/2;
        KDNode* cur = new KDNode(points.at(mid));
        this->isize++; //size plus 1
        cur->left = buildSubtree(points,start,mid,(curDim+1)%numDim,height); // build left subtree
        cur->right = buildSubtree(points,mid+1,end,(curDim+1)%numDim,height); // build right subtree
        return cur;
    }

    /** Helper function to calculate the height of KDT. */
    static int calHeight(KDNode* root) {
      if(root==nullptr) return 0;
      int leftH = calHeight(root->left);
      int rightH = calHeight(root->right);
      return leftH>rightH?leftH+1:rightH+1;
    }

    /** Helper function of finding nearest neightbor */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
      threshold = numeric_limits<double>::max(); // initialize threshold as max double
      if(root==nullptr) return; 
      root->point.setDistToQuery(queryPoint); // initialize the threshold
      nearestNeighbor = root->point;
      threshold = root->point.distToQuery;
      forwardSearch(node, queryPoint, 0); // go to another helper function
    }

    /** Helper function 2 of finding nearest neightbor */
    void forwardSearch(KDNode* node, Point& queryPoint, unsigned int curDim){
      if(node == nullptr) return; // end point
      double queryValue = queryPoint.valueAt(curDim); // get query point value at this dimension
      double kdtValue = node->point.valueAt(curDim); // get node value at this dimension
      // decide which way to go
      KDNode* next = queryValue < kdtValue ? node->left : node->right; 
      KDNode* other = queryValue < kdtValue ? node->right : node->left;
      // renew threshold
      node->point.setDistToQuery(queryPoint);
      if(node->point.distToQuery < threshold){
            this->nearestNeighbor = node->point;
            this->threshold = node->point.distToQuery; // renew threshold
      }
      // recursive get the last leaf
      forwardSearch(next, queryPoint, (curDim+1)%numDim);
      // renew threshold
      if(next!=nullptr){
        next->point.setDistToQuery(queryPoint);
        if(next->point.distToQuery < threshold){
            this->nearestNeighbor = next->point;
            this->threshold = next->point.distToQuery;
        }
      }
      // judage whether use another leaf node
      if(other!=nullptr){
        other->point.setDistToQuery(queryPoint);
        if(other->point.distToQuery < this->threshold){
          this->threshold = other->point.distToQuery;
          this->nearestNeighbor = other->point; // renew threshold
        }
      }
      return;
    }


    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** Delete all the node in this KDT. */
    static void deleteAll(KDNode* n) {
      if(n==nullptr) return;
      deleteAll(n->left);
      deleteAll(n->right);
      delete n;
    }

    // Add your own helper methods here
    public:
      /** Print the Tree to confirm build. */
      void print(){
        printKDT(root);
      }
      /** Helper function to print Tree. */
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
        cout<<""<<endl;
      }
};


#endif  // KDT_HPP
