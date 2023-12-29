struct MatrixTask {
	int m;
	int n;

	bool hasTask() {
		return !(n < 0 || m < 0);
	}
};