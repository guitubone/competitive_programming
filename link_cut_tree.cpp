namespace lct1 {
	// LinkCut tree with path queries. Query complexity is O(log(n)) amortized.
	// Based on Daniel Sleator's implementation http://www.codeforces.com/contest/117/submission/860934


	// Modify the following 5 methods to implement your custom operations on the tree.
	// This example implements Add/Sum operations. Operations like Add/Max, Set/Max can also be implemented.
	int modifyOperation(int x, int y) {
		return x + y;
	}

	// query (or combine) operation
	int queryOperation(int leftValue, int rightValue) {
		return leftValue + rightValue;
	}

	int getNeutralDelta() {
		return 0;
	}

	int getNeutralValue() {
		return 0;
	}

	int deltaEffectOnSegment(int delta, int segmentLength) {
		if (delta == getNeutralDelta()) return getNeutralDelta();
		// Here you must write a fast equivalent of following slow code:
		// int result = delta;
		// for (int i = 1; i < segmentLength; i++) result = queryOperation(result, delta);
		// return result;
		return delta * segmentLength;
	}

	// generic code
	int joinValueWithDelta(int value, int delta) {
		if (delta == getNeutralDelta()) return value;
		return modifyOperation(value, delta);
	}

	int joinDeltas(int delta1, int delta2) {
		if (delta1 == getNeutralDelta()) return delta2;
		if (delta2 == getNeutralDelta()) return delta1;
		return modifyOperation(delta1, delta2);
	}

	class Node;
	int getSize(Node* root);
	int getSubTreeValue(Node* root);
	void connect(Node* ch, Node* p, bool isLeftChild);

	struct Node {
		int nodeValue;
		int subTreeValue;
		int delta; // delta affects nodeValue, subTreeValue, left->delta and right->delta
		int size;
		bool revert;
		Node *left;
		Node *right;
		Node *parent;

		Node(int value) {
			nodeValue = value;
			subTreeValue = value;
			delta = getNeutralDelta();
			size = 1;

			revert = false;
			left = right = parent = NULL;
		}

		// tests whether x is a root of a splay tree
		bool isRoot() {
			return parent == NULL || (parent->left != this && parent->right != this);
		}

		void push() {
			if (revert) {
				revert = false;
				Node* t = left;
				left = right;
				right = t;
				if (left != NULL)
					left->revert = !left->revert;
				if (right != NULL)
					right->revert = !right->revert;
			}

			nodeValue = joinValueWithDelta(nodeValue, delta);
			subTreeValue = joinValueWithDelta(subTreeValue, deltaEffectOnSegment(delta, size));
			if (left != NULL)
				left->delta = joinDeltas(left->delta, delta);
			if (right != NULL)
				right->delta = joinDeltas(right->delta, delta);
			delta = getNeutralDelta();
		}

		void update() {
			subTreeValue = queryOperation(queryOperation(getSubTreeValue(left), joinValueWithDelta(nodeValue, delta)), getSubTreeValue(right));
			size = 1 + getSize(left) + getSize(right);
		}
	};

	int getSize(Node* root) {
		return root == NULL ? 0 : root->size;
	}

	int getSubTreeValue(Node* root) {
		return root == NULL ? getNeutralValue() : joinValueWithDelta(root->subTreeValue, deltaEffectOnSegment(root->delta, root->size));
	}

	void connect(Node* ch, Node* p, bool isLeftChild = false) {
		if (ch != NULL)
			ch->parent = p;
		if (isLeftChild)
			p->left = ch;
		else
			p->right = ch;
	}

	// rotates edge (x, x->parent)
	//        g            g
	//       /            /
	//      p            x
	//     / \    ->    / \
	//    x  p.r      x.l  p
	//   / \              / \
	// x.l x.r          x.r p.r
	void rotate(Node* x) {
		Node* p = x->parent;
		Node* g = p->parent;
		bool isRootP = p->isRoot();
		bool leftChildX = (x == p->left);

		// create 3 edges: (x.r(l),p), (p,x), (x,g)
		connect(leftChildX ? x->right : x->left, p, leftChildX);
		connect(p, x, !leftChildX);
		if (isRootP) x->parent = g;
		else connect(x, g, p == g->left);
		p->update();
	}

	// brings x to the root, balancing tree
	//
	// zig-zig case
	//        g                                  x
	//       / \               p                / \
	//      p  g.r rot(p)    /   \     rot(x) x.l  p
	//     / \      -->    x       g    -->       / \
	//    x  p.r          / \     / \           x.r  g
	//   / \            x.l x.r p.r g.r             / \
	// x.l x.r                                    p.r g.r
	//
	// zig-zag case
	//      g               g
	//     / \             / \               x
	//    p  g.r rot(x)   x  g.r rot(x)    /   \
	//   / \      -->    / \      -->    p       g
	// p.l  x           p  x.r          / \     / \
	//     / \         / \            p.l x.l x.r g.r
	//   x.l x.r     p.l x.l
	void splay(Node* x) {
		while (!x->isRoot()) {
			Node* p = x->parent;
			Node* g = p->parent;
			if (!p->isRoot())
				g->push();
			p->push();
			x->push();
			if (!p->isRoot())
				rotate((x == p->left) == (p == g->left) ? p/*zig-zig*/ : x/*zig-zag*/);
			rotate(x);
		}
		x->push();
		x->update();
	}

	// makes node x the root of the virtual tree, and also x becomes the leftmost node in its splay tree
	Node* expose(Node* x) {
		Node* last = NULL;
		for (Node* y = x; y != NULL; y = y->parent) {
			splay(y);
			y->left = last;
			last = y;
		}
		splay(x);
		return last;
	}

	void makeRoot(Node* x) {
		expose(x);
		x->revert = !x->revert;
	}

	bool connected(Node* x, Node* y) {
		if (x == y)
			return true;
		expose(x);
		// now x->parent is NULL
		expose(y);
		return x->parent != NULL;
	}

	void link(Node* x, Node* y) {
		if (connected(x, y))
			assert(false);
		makeRoot(x);
		x->parent = y;
	}

	void cut(Node* x, Node* y) {
		makeRoot(x);
		expose(y);
		// check that exposed path consists of a single edge (y,x)
		if (y->right != x || x->left != NULL)
			assert(false);
		y->right->parent = NULL;
		y->right = NULL;
	}

	int query(Node* from, Node* to) {
		makeRoot(from);
		expose(to);
		return getSubTreeValue(to);
	}

	void modify(Node* from, Node* to, int delta) {
		makeRoot(from);
		expose(to);
		to->delta = joinDeltas(to->delta, delta);
	}
};

