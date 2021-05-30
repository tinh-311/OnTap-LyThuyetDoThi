#include"Header.h"

void insertLast(Node*& l, Node* p) {
	if (l == NULL) {
		l = p;
	}
	else {
		for (Node* i = l; i != NULL; i = i->link) {
			if (i->link == NULL) {
				i->link = p;
				break;
			}
		}
	}
}

bool docFileMaTranKe(const char* fileName, AdjacencyMatrix& m) {
	FILE* f;
	fopen_s(&f, fileName, "r");
	if (f == NULL)
		return false;

	fscanf_s(f, "%d", &m.n);
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			fscanf_s(f, "%d", &m.mt[i][j]);
		}
	}

	fclose(f);
	return true;
}

void xuatMaTranKe(AdjacencyMatrix m) {
	cout << m.n << endl;
	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			cout << m.mt[i][j] << " ";
		}
		cout << endl;
	}
}

bool docFileDanhSachKe(const char* fileName, AdjacencyList& l) {
	ifstream f;
	f.open(fileName, ios::in);
	if (f.fail())
		return false;

	f >> l.n;
	for (int i = 0; i < l.n; i++) {
		l.ds[i] = NULL;
	}

	for (int i = 0; i < l.n; i++) {
		int k;
		f >> k;

		for (int j = 0; j < k; j++) {
			Node* p = new Node;
			f >> p->dinhKe;
			f >> p->trongSo;
			p->link = NULL;

			// C1
			insertLast(l.ds[i], p);

			// c2 - them dau danh sach lien ket
			/*p->link = l.ds[i];
			l.ds[i] = p;*/
		}
	}
	f.close();
	return true;
}

void xuatDanhSachKe(AdjacencyList l) {
	cout << l.n << endl;
	for (int i = 0; i < l.n; i++) {
		Node* p = l.ds[i];
		while (p != NULL) {
			cout << p->dinhKe << " " << p->trongSo << " ";
			p = p->link;
		}
		cout << endl;
	}
}

void xuatCanh(Edge e) {
	cout << e.dinhDau << "->" << e.dinhCuoi << " - Trong so: " << e.trongSo << endl;
}

void xuatDanhSachCanh(ArrayEdge e) {
	cout << "So canh: " << e.n << endl;
	for (int i = 0; i < e.n; i++) {
		xuatCanh(e.ds[i]);
	}
}

//---------- B. Chuyển đổi cấu trúc ----------

//1. Viết hàm chuyển Ma trận kề sang danh sách kề
AdjacencyList MTK_to_DSK(AdjacencyMatrix MTKe) {
	AdjacencyList l;
	l.n = MTKe.n;

	for (int i = 0; i < l.n; i++) {
		l.ds[i] = NULL;
	}

	for (int i = 0; i < MTKe.n; i++) {
		for (int j = 0; j < MTKe.n; j++) {
			if (MTKe.mt[i][j] != 0) {
				Node* p = new Node;
				p->dinhKe = j;
				p->trongSo = MTKe.mt[i][j];
				p->link = NULL;

				insertLast(l.ds[i], p);
			}
		}
	}

	return l;
}

//2. Viết hàm chuyển Ma trận kề sang danh sách cạnh
ArrayEdge MTK_to_DSC(AdjacencyMatrix MTKe) {
	ArrayEdge e;
	e.n = 0;

	for (int i = 0; i < MTKe.n; i++) {
		for (int j = 0; j < MTKe.n; j++) {
			if (MTKe.mt[i][j] != 0) {
				Edge c = { i,j,MTKe.mt[i][j] };
				e.ds[e.n++] = c;
			}
		}
	}

	return e;
}

// 3. Viết hàm chuyển danh sách kề sang ma trận kề
AdjacencyMatrix DSK_to_MTK(AdjacencyList DSKe) {
	AdjacencyMatrix m;
	m.n = DSKe.n;

	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.mt[i][j] = 0;
		}
	}

	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			m.mt[i][p->dinhKe] = p->trongSo;
			p = p->link;
		}
	}

	return m;
}

// 4. Viết hàm chuyển danh sách kề sang danh sách cạnh
ArrayEdge DSK_to_DSC(AdjacencyList DSKe) {
	ArrayEdge e;
	e.n = 0;

	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			Edge c = { i, p->dinhKe, p->trongSo };

			e.ds[e.n++] = c;

			p = p->link;
		}
	}

	return e;
}

// 5. Viết hàm chuyển danh sách cạnh và 1 số nguyên là số đỉnh của đồ thị sang ma trận kề
AdjacencyMatrix DSC_to_MTK(ArrayEdge DSC, int sodinh) {
	AdjacencyMatrix m;
	m.n = sodinh;

	for (int i = 0; i < m.n; i++) {
		for (int j = 0; j < m.n; j++) {
			m.mt[i][j] = 0;
		}
	}

	for (int i = 0; i < DSC.n; i++) {
		m.mt[DSC.ds[i].dinhDau][DSC.ds[i].dinhCuoi] = DSC.ds[i].trongSo;
	}

	return m;
}

// 6. Viết hàm chuyển danh sách cạnh và 1 số nguyên là số đỉnh của đồ thị sang danh sách kề
AdjacencyList DSC_to_DSK(ArrayEdge DSC, int sodinh) {
	AdjacencyList l;
	l.n = sodinh;

	for (int i = 0; i < l.n; i++) {
		l.ds[i] = NULL;
	}

	for (int i = 0; i < DSC.n; i++) {
		Edge c = DSC.ds[i];

		Node* p = new Node;
		p->dinhKe = c.dinhCuoi;
		p->trongSo = c.trongSo;
		p->link = NULL;

		insertLast(l.ds[c.dinhDau], p);
	/*	p->link = l.ds[c.dinhDau];
		l.ds[c.dinhDau] = p;*/
	}

	return l;
}

//---------- C. Tính Bậc ----------

// 1. Viết hàm tính bậc vào của 1 đỉnh (Danh sách kề)
int BacVao(AdjacencyList DSKe, VERTEX u) {
	int bac = 0;
	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			if (p->dinhKe == u) {
				bac++;
			}

			p = p->link;
		}
	}

	return bac;
}

// 2. Viết hàm tính bậc ra của 1 đỉnh u (Danh sách kề)
int TinhBacRa(AdjacencyList DSKe, VERTEX u) {
	int bac = 0;
	if (DSKe.ds[u] == NULL)
		return bac;

	Node* p = DSKe.ds[u];
	while (p != NULL) {
		bac++;
		p = p->link;
	}

	return bac;
}

// 3. Viết hàm tính bậc vào của 1 đỉnh (Ma trận kề)
int BacVao(AdjacencyMatrix x, VERTEX u) {
	int bac = 0;
	for (int i = 0; i < x.n; i++) {
		if (x.mt[i][u] != 0) {
			bac++;
		}
	}

	return bac;
}

// 4. Viết hàm tính bậc ra của 1 đỉnh u (Ma trận kề)
int TinhBacRa(AdjacencyMatrix x, VERTEX u) {
	int bac = 0;

	for (int i = 0; i < x.n; i++) {
		if (x.mt[u][i] != 0)
			bac++;
	}

	return bac;
}

// 5. Viết hàm trả về đỉnh có bậc lớn nhất trong đồ thị (Ma trận kề)
VERTEX DinhBacMax(AdjacencyMatrix x) {
	if (x.n == 0)
		return -1;

	int dinhBacMax = 0;
	int max = BacVao(x, 0) + TinhBacRa(x, 0);
	for (int i = 1; i < x.n; i++) {
		int k = BacVao(x, i);
		if (k > max) {
			max = k;
			dinhBacMax = i;
		}
	}

	return dinhBacMax;
}

// 6. Viết hàm trả về đỉnh có bậc nhỏ nhất trong đồ thị (Ma trận kề)
VERTEX DinhBacMin(AdjacencyMatrix x) {
	if (x.n == 0)
		return -1;

	int dinhBacMin = 0;
	int min = BacVao(x, 0) + TinhBacRa(x, 0);
	for (int i = 1; i < x.n; i++) {
		int k = BacVao(x, i);
		if (k < min) {
			min = k;
			dinhBacMin = i;
		}
	}

	return dinhBacMin;
}

// 7. Viết hàm trả về đỉnh có bậc lớn nhất trong đồ thị (Danh sách kề)
VERTEX DinhBacMax(AdjacencyList x) {
	if (x.n == 0)
		return -1;

	int dinhBacMax = 0;
	int max = BacVao(x, 0) + TinhBacRa(x, 0);

	for (int i = 1; i < x.n; i++) {
		int k = BacVao(x, i) + TinhBacRa(x, i);
		if (k > max) {
			max = k;
			dinhBacMax = i;
		}
	}

	return dinhBacMax;
}

// 8. Viết hàm trả về đỉnh có bậc nhỏ nhất trong đồ thị (Danh sách kề)
VERTEX DinhBacMin(AdjacencyList x) {
	if (x.n == 0)
		return -1;

	int dinhBacMin = 0;
	int min = BacVao(x, 0) + TinhBacRa(x, 0);

	for (int i = 1; i < x.n; i++) {
		int k = BacVao(x, i);
		if (k < min) {
			min = k;
			dinhBacMin = i;
		}
	}

	return dinhBacMin;
}

// 9. Viết hàm tìm đỉnh v kề đỉnh u có bậc lớn nhất (Ma trận kề). Hàm trả về 1 nếu tìm được và trả về 0 nếu không tìm được
int TimĐinhKe_BacMax(AdjacencyMatrix MTKe, VERTEX u, VERTEX& v) {
	
	int flag = 0;
	int bac;
	for (int i = 0; i < MTKe.n; i++) {
		if (MTKe.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				v = i;
				bac = BacVao(MTKe, i) + TinhBacRa(MTKe, i);
			}
			else if (BacVao(MTKe, i) + TinhBacRa(MTKe, i) > bac) {
				bac = BacVao(MTKe, i) + TinhBacRa(MTKe, i);
				v = i;
			}
		}
	}

	return flag;
}

// 10. Viết hàm tìm đỉnh v kề đỉnh u có bậc nhỏ nhất (Ma trận kề)
int TimĐinhKe_BacMin(AdjacencyMatrix MTKe, VERTEX u, VERTEX& v) {
	int flag = 0;
	int bac;
	for (int i = 0; i < MTKe.n; i++) {
		if (MTKe.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				v = i;
				bac = BacVao(MTKe, i) + TinhBacRa(MTKe, i);
			}
			else if (BacVao(MTKe, i) + TinhBacRa(MTKe, i) < bac) {
				bac = BacVao(MTKe, i) + TinhBacRa(MTKe, i);
				v = i;
			}
		}
	}

	return flag;
}

// 11. Viết hàm tìm đỉnh v kề đỉnh u có bậc lớn nhất (Danh sách kề). Hàm trả về 1 nếu tìm được và trả về 0 nếu không tìm được.
int TimĐinhKe_BacMax(AdjacencyList DSKe, VERTEX u, VERTEX& v) {
	if (DSKe.ds[u] == NULL)
		return 0;

	int bacMax = BacVao(DSKe, DSKe.ds[u]->dinhKe) + TinhBacRa(DSKe, DSKe.ds[u]->dinhKe);
	v = DSKe.ds[u]->dinhKe;

	Node* p = DSKe.ds[u]->link;
	while (p != NULL) {
		int k = BacVao(DSKe, p->dinhKe) + TinhBacRa(DSKe, p->dinhKe);
		if (k > bacMax) {
			bacMax = k;
			v = p->dinhKe;
		}
		p = p->link;
	}

	return 1;
}

// 12. Viết hàm tìm đỉnh v kề đỉnh u có bậc nhỏ nhất (Danh sách kề). Hàm trả về 1 nếu tìm được và trả về 0 nếu không tìm được
int TimĐinhKe_BacMin(AdjacencyList DSKe, VERTEX u, VERTEX& v) {
	if (DSKe.ds[u] == NULL)
		return 0;

	int bacMin = BacVao(DSKe, DSKe.ds[u]->dinhKe) + TinhBacRa(DSKe, DSKe.ds[u]->dinhKe);
	v = DSKe.ds[u]->dinhKe;

	Node* p = DSKe.ds[u]->link;
	while (p != NULL) {
		int k = BacVao(DSKe, p->dinhKe) + TinhBacRa(DSKe, p->dinhKe);
		if (k < bacMin) {
			bacMin = k;
			v = p->dinhKe;
		}
		p = p->link;
	}

	return 1;
}

// ---------- D. Tìm Cạnh ----------

// 1. Viết hàm tìm cạnh lớn nhất trong đồ thị (Ma trận kề), hàm trả về 1 nếu có cạnh lớn nhất, trả về 0 nếu không có cạnh lớn nhất
int TimCanhMax(AdjacencyMatrix MTKe, Edge& CanhMax) {
	int flag = 0;
	int max;
	for (int i = 0; i < MTKe.n; i++) {
		for (int j = 0; j < MTKe.n; j++) {
			if (MTKe.mt[i][j] != 0) {
				if (flag == 0) {
					flag = 1;
					max = MTKe.mt[i][j];
					CanhMax.dinhDau = i;
					CanhMax.dinhCuoi = j;
					CanhMax.trongSo = MTKe.mt[i][j];
				}
				else if (max < MTKe.mt[i][j]) {
					max = MTKe.mt[i][j];
					CanhMax.dinhDau = i;
					CanhMax.dinhCuoi = j;
					CanhMax.trongSo = MTKe.mt[i][j];
				}
			}
		}
	}

	return flag;
}

// 2. Viết hàm tìm cạnh nhỏ nhất trong đồ thị (Ma trận kề), hàm trả về 1 nếu có cạnh nhỏ nhất, trả về 0 nếu không có cạnh nhỏ nhất
int TimCanhMin(AdjacencyMatrix MTKe, Edge& CanhMin) {
	int flag = 0;
	int min;
	for (int i = 0; i < MTKe.n; i++) {
		for (int j = 0; j < MTKe.n; j++) {
			if (MTKe.mt[i][j] != 0) {
				if (flag == 0) {
					flag = 1;
					min = MTKe.mt[i][j];
					CanhMin.dinhDau = i;
					CanhMin.dinhCuoi = j;
					CanhMin.trongSo = MTKe.mt[i][j];
				}
				else if (min > MTKe.mt[i][j]) {
					min = MTKe.mt[i][j];
					CanhMin.dinhDau = i;
					CanhMin.dinhCuoi = j;
					CanhMin.trongSo = MTKe.mt[i][j];
				}
			}
		}
	}

	return flag;
}

// // 3. Viết hàm tìm cạnh lớn nhất trong đồ thị (Danh sách kề), hàm trả về 1 nếu có cạnh lớn nhất, trả về 0 nếu không có cạnh lớn nhất
int TimCanhMax(AdjacencyList DSKe, Edge& CanhMax) {
	int flag = 0;
	int max;

	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			if (flag == 0) {
				flag = 1;
				max = p->trongSo;
				CanhMax.dinhDau = i;
				CanhMax.dinhCuoi = p->dinhKe;
				CanhMax.trongSo = p->trongSo;
			}
			else if (max < p->trongSo) {
				max = p->trongSo;
				CanhMax.dinhDau = i;
				CanhMax.dinhCuoi = p->dinhKe;
				CanhMax.trongSo = p->trongSo;
			}
			p = p->link;
		}
	}

	return flag;
}

// 4. Viết hàm tìm cạnh nhỏ nhất trong đồ thị (Danh sách kề), hàm trả về 1 nếu có cạnh nhỏ nhất, trả về 0 nếu không có cạnh nhỏ nhất
int TimCanhMin(AdjacencyList DSKe, Edge& CanhMin) {
	int flag = 0;
	int min;

	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			if (flag == 0) {
				flag = 1;
				min = p->trongSo;
				CanhMin.dinhDau = i;
				CanhMin.dinhCuoi = p->dinhKe;
				CanhMin.trongSo = p->trongSo;
			}
			else if (min > p->trongSo) {
				min = p->trongSo;
				CanhMin.dinhDau = i;
				CanhMin.dinhCuoi = p->dinhKe;
				CanhMin.trongSo = p->trongSo;
			}
			p = p->link;
		}
	}

	return flag;
}

// 5. Viết hàm trả về tổng trọng số của các cạnh trong đồ thị (Ma trận kề)
int TongTrongSo(AdjacencyMatrix MTKe) {
	int tongTS = 0;
	for (int i = 0; i < MTKe.n; i++) {
		for (int j = 0; j < MTKe.n; j++) {
			if (MTKe.mt[i][j] != 0) {
				tongTS += MTKe.mt[i][j];
			}
		}
	}

	return tongTS;
}

// 6. Viết hàm trả về tổng trọng số của các cạnh trong đồ thị (Danh sách kề)
int TongTrongSo(AdjacencyList DSKe) {
	int tongTS = 0;
	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			tongTS += p->trongSo;
			p = p->link;
		}
	}

	return tongTS;
}

// 7. Viết hàm trả về tổng trọng số các cạnh xuất phát từ đỉnh u (ma trận kề)
int TongTrongSoTuU(AdjacencyMatrix MTKe, VERTEX u) {
	int tongTS = 0;
	for (int i = 0; i < MTKe.n; i++) {
		tongTS += MTKe.mt[u][i];
	}

	return tongTS;
}

// 8. Viết hàm trả về tổng trọng số các cạnh đi vào đỉnh u (ma trận kề)
int TongTrongSoVaoU(AdjacencyMatrix MTKe, VERTEX u) {
	int tongTS = 0;

	for (int i = 0; i < MTKe.n; i++) {
		tongTS += MTKe.mt[i][u];
	}

	return tongTS;
}

// 9. Viết hàm trả về tổng trọng số các cạnh xuất phát từ đỉnh u (danh sách kề)
int TongTrongSoTuU(AdjacencyList DSKe, VERTEX u) {
	int tongTS = 0;
	Node* p = DSKe.ds[u];
	while (p != NULL) {
		tongTS += p->trongSo;
		p = p->link;
	}

	return tongTS;
}

// 10.Viết hàm trả về tổng trọng số các cạnh đi vào đỉnh u (danh sách kề)
int TongTrongSoVaoU(AdjacencyList DSKe, VERTEX u) {
	int tongTS = 0;

	for (int i = 0; i < DSKe.n; i++) {
		Node* p = DSKe.ds[i];
		while (p != NULL) {
			if (p->dinhKe == u) {
				tongTS += p->trongSo;
			}
			p = p->link;
		}
	}

	return tongTS;
}

// 11.Viết hàm tìm cạnh có trọng số lớn nhất kề với đỉnh u (ma trận kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int CanhCoTrongSoLonNhat(AdjacencyMatrix x, int u, Edge& CanhKeMax) {
	int flag = 0;
	int ts;
	for (int i = 0; i < x.n; i++) {
		if (x.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				ts = x.mt[u][i];
				CanhKeMax.dinhDau = u;
				CanhKeMax.dinhCuoi = i;
				CanhKeMax.trongSo = x.mt[u][i];
			}
			else if (ts < x.mt[u][i]) {
				ts = x.mt[u][i];
				CanhKeMax.dinhDau = u;
				CanhKeMax.dinhCuoi = i;
				CanhKeMax.trongSo = x.mt[u][i];
			}
		}
	}

	return flag;
}

// 12.Viết hàm tìm cạnh có trọng số lớn nhất kề với đỉnh u (danh sách kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int CanhCoTrongSoLonNhat(AdjacencyList x, int u, Edge& CanhKeMax) {
	if (x.ds[u] == NULL)
		return 0;

	int ts = x.ds[u]->trongSo;
	CanhKeMax.dinhDau = u;
	CanhKeMax.dinhCuoi = x.ds[u]->dinhKe;
	CanhKeMax.trongSo = x.ds[u]->trongSo;

	Node* p = x.ds[u]->link;
	while (p != NULL) {
		if (ts < p->trongSo) {
			ts = p->trongSo;
			CanhKeMax.dinhDau = u;
			CanhKeMax.dinhCuoi = p->dinhKe;
			CanhKeMax.trongSo = p->trongSo;
		}
		p = p->link;
	}

	return 1;
}

// 13.Viết hàm tìm cạnh có trọng số nhỏ nhất kề với đỉnh u (ma trận kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int CanhCoTrongSoNhoNhat(AdjacencyMatrix x, int u, Edge& CanhKeMin) {
	int flag = 0;
	int ts;
	for (int i = 0; i < x.n; i++) {
		if (x.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				ts = x.mt[u][i];
				CanhKeMin.dinhDau = u;
				CanhKeMin.dinhCuoi = i;
				CanhKeMin.trongSo = x.mt[u][i];
			}
			else if (ts > x.mt[u][i]) {
				ts = x.mt[u][i];
				CanhKeMin.dinhDau = u;
				CanhKeMin.dinhCuoi = i;
				CanhKeMin.trongSo = x.mt[u][i];
			}
		}
	}

	return flag;
}

// 14.Viết hàm tìm cạnh có trọng số nhỏ nhất kề với đỉnh u (danh sách kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int CanhCoTrongSoNhoNhat(AdjacencyList x, int u, Edge& CanhKeMin) {
	if (x.ds[u] == NULL)
		return 0;

	int ts = x.ds[u]->trongSo;
	CanhKeMin.dinhDau = u;
	CanhKeMin.dinhCuoi = x.ds[u]->dinhKe;
	CanhKeMin.trongSo = x.ds[u]->trongSo;

	Node* p = x.ds[u]->link;
	while (p != NULL) {
		if (ts > p->trongSo) {
			ts = p->trongSo;
			CanhKeMin.dinhDau = u;
			CanhKeMin.dinhCuoi = p->dinhKe;
			CanhKeMin.trongSo = p->trongSo;
		}
		p = p->link;
	}

	return 1;
}

// 15.Viết hàm tìm đỉnh v kề với đỉnh u có trọng số cạnh (u,v) nhỏ nhất (Ma trận kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int TimDinhke_MinTrongso(AdjacencyMatrix MTKe, VERTEX u, VERTEX& v) {
	int flag = 0;
	int ts;

	for (int i = 0; i < MTKe.n; i++) {
		if (MTKe.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				ts = MTKe.mt[u][i];
				v = i;
			}
			else if (MTKe.mt[u][i] < ts) {
				ts = MTKe.mt[u][i];
				v = i;
			}
		}
	}

	return flag;
}

// 16.Viết hàm tìm đỉnh v kề với đỉnh u có trọng số cạnh (u,v) lớn nhất (Ma trận kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int TimDinhke_MaxTrongso(AdjacencyMatrix MTKe, VERTEX u, VERTEX& v) {
	int flag = 0;
	int ts;

	for (int i = 0; i < MTKe.n; i++) {
		if (MTKe.mt[u][i] != 0) {
			if (flag == 0) {
				flag = 1;
				ts = MTKe.mt[u][i];
				v = i;
			}
			else if (MTKe.mt[u][i] > ts) {
				ts = MTKe.mt[u][i];
				v = i;
			}
		}
	}

	return flag;
}

// 17.Viết hàm tìm đỉnh v kề với đỉnh u có trọng số cạnh (u,v) nhỏ nhất (Danh sách kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int TimDinhke_MinTrongso(AdjacencyList DSKe, VERTEX u, VERTEX& v) {
	if (DSKe.ds[u] == NULL)
		return 0;

	int ts = DSKe.ds[u]->trongSo;
	v = DSKe.ds[u]->dinhKe;

	Node* p = DSKe.ds[u]->link;
	while (p != NULL) {
		if (p->trongSo < ts) {
			ts = p->trongSo;
			v = p->dinhKe;
		}

		p = p->link;
	}

	return 1;
}

// 18.Viết hàm tìm đỉnh v kề với đỉnh u có trọng số cạnh (u,v) lớn nhất (Danh sách kề). Hàm trả về 1 nếu tìm được, trả về 0 nếu không tìm được
int TimDinhke_MaxTrongso(AdjacencyList DSKe, VERTEX u, VERTEX& v) {
	if (DSKe.ds[u] == NULL)
		return 0;

	int ts = DSKe.ds[u]->trongSo;
	v = DSKe.ds[u]->dinhKe;

	Node* p = DSKe.ds[u]->link;
	while (p != NULL) {
		if (p->trongSo > ts) {
			ts = p->trongSo;
			v = p->dinhKe;
		}

		p = p->link;
	}

	return 1;
}

void meNu() {
	AdjacencyList l;
	l.n = 0;

	AdjacencyMatrix m;
	m.n = 0;

	ArrayEdge e;
	e.n = 0;

	bool kt = true;
	while (kt) {
		system("cls");
		cout << "\n\t\t\t====== MENU ======\n" << endl;
		cout << "0. Thoat." << endl;
		cout << "1. Doc file ma tran ke." << endl;
		cout << "2. Xuat ma tran ke." << endl;
		cout << "3. Doc file danh sach ke." << endl;
		cout << "4. Xuat danh sach ke." << endl;
		cout << "5. Chuyen ma tran ke sang danh sach ke." << endl;
		cout << "6. Chuyen ma tran ke sang danh sach canh." << endl;
		cout << "7. Xuat danh sach canh." << endl;
		cout << "8. Chuyen danh sach ke sang ma tran ke." << endl;
		cout << "9. Chuyen danh sach ke sang danh sach canh." << endl;
		cout << "10. Chuyen danh sach canh sang ma tran ke." << endl;
		cout << "11. Chuyen danh sach canh sang danh sach ke." << endl;
		cout << "12. Tinh bac vao cua mot dinh (Danh sach ke)." << endl;
		cout << "13. Tinh bac ra cua mot dinh (Danh sach ke)." << endl;
		cout << "14. Tinh bac vao cua mot dinh (Ma tran ke)." << endl;
		cout << "15. Tinh bac ra cua mot dinh (Ma tran ke)." << endl;
		cout << "16. Tim dinh co bac lon nhat (Ma tran ke)." << endl;
		cout << "17. Tim dinh co bac nho nhat (Ma tran ke)." << endl;
		cout << "18. Tim dinh co bac lon nhat (Danh sach ke)." << endl;
		cout << "19. Tim dinh co bac nho nhat (Danh sach ke)." << endl;
		cout << "20. Tim dinh ke co bac lon nhat voi mot dinh (Ma tran ke)." << endl;
		cout << "21. Tim dinh ke co bac nho nhat voi mot dinh (Ma tran ke)." << endl;
		cout << "22. Tim dinh ke co bac lon nhat voi mot dinh (Danh sach ke)." << endl;
		cout << "23. Tim dinh ke co bac nho nhat voi mot dinh (Danh sach ke)." << endl;
		cout << "24. Tim canh lon nhat trong do thi (Ma tran ke)." << endl;
		cout << "25. Tim canh nho nhat trong do thi (Ma tran ke)." << endl;
		cout << "26. Tim canh lon nhat trong do thi (Danh sach ke)." << endl;
		cout << "27. Tim canh nho nhat trong do thi (Danh sach ke)." << endl;
		cout << "28. Tinh tong trong so cua cac canh trong do thi (Ma tran ke)." << endl;
		cout << "29. Tinh tong trong so cua cac canh trong do thi (Danh sach ke)." << endl;
		cout << "30. Tinh tong trong so cac canh xuat phat tu dinh u (Ma tran ke)." << endl;
		cout << "31. Tinh tong trong so cac canh di vao dinh u (Ma tran ke)." << endl;
		cout << "32. Tinh tong trong so cac canh xuat phat tu dinh u (Danh sach ke)." << endl;
		cout << "33. Tinh tong trong so cac canh di vao dinh u (Danh sach ke)." << endl;
		cout << "34. Tim canh co trong so lon nhat ke voi dinh u (Ma tran ke)." << endl;
		cout << "35. Tim canh co trong so lon nhat ke voi dinh u (Danh sach ke)." << endl;
		cout << "36. Tim canh co trong so nho nhat ke voi dinh u (Ma tran ke)." << endl;
		cout << "37. Tim canh co trong so nho nhat ke voi dinh u (Danh sach ke)." << endl;
		cout << "38. Tim dinh v ke voi dinh u co trong so canh (u, v) nho nhat (Ma tran ke)." << endl;
		cout << "39. Tim dinh v ke voi dinh u co trong so canh (u, v) lon nhat (Ma tran ke)." << endl;
		cout << "40. Tim dinh v ke voi dinh u co trong so canh (u, v) nho nhat (Danh sach ke)." << endl;
		cout << "41. Tim dinh v ke voi dinh u co trong so canh (u, v) lon nhat (Danh sach ke)." << endl;
		cout << "\n\t\t\t====== END ======\n" << endl;

		int luaChon;
		cout << "Nhap lua chon: ";
		cin >> luaChon;

		switch (luaChon) {
		case 0: {
			kt = false;
			break;
		}
		case 1: {
			bool check = docFileMaTranKe("MTK.txt", m);
			if (check)
				cout << "Doc file thanh cong !" << endl;
			else
				cout << "Loi doc file !" << endl;
			break;
		}
		case 2: {
			xuatMaTranKe(m);
			break;
		}
		case 3: {
			bool check = docFileDanhSachKe("DSK.txt", l);
			if (check)
				cout << "Doc file thanh cong !" << endl;
			else
				cout << "Loi doc file !" << endl;
			break;
		}
		case 4: {
			xuatDanhSachKe(l);
			break;
		}
		case 5: {
			l = MTK_to_DSK(m);
			break;
		}
		case 6: {
			e = MTK_to_DSC(m);
			break;
		}
		case 7: {
			xuatDanhSachCanh(e);
			break;
		}
		case 8: {
			m = DSK_to_MTK(l);
			break;
		}
		case 9: {
			e = DSK_to_DSC(l);
			break;
		}
		case 10: {
			int soDinh = l.n;
			m = DSC_to_MTK(e, soDinh);

			break;
		}
		case 11: {
			int soDinh = m.n;
			l = DSC_to_DSK(e, soDinh);
			break;
		}
		case 12: {
			int dinh;
			do {
				cout << "Nhap dinh: ";
				cin >> dinh;
				if (dinh < 0 || dinh >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (dinh < 0 || dinh >= l.n);

			int bac = BacVao(l, dinh);

			cout << "Bac vao cua dinh " << dinh << " la: " << bac << endl;

			break;
		}
		case 13: {
			int dinh;
			do {
				cout << "Nhap dinh: ";
				cin >> dinh;
				if (dinh < 0 || dinh >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (dinh < 0 || dinh >= l.n);

			int bac = TinhBacRa(l, dinh);

			cout << "Bac ra cua dinh " << dinh << " la: " << bac << endl;

			break;
		}
		case 14: {
			int dinh;
			do {
				cout << "Nhap dinh: ";
				cin >> dinh;
				if (dinh < 0 || dinh >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (dinh < 0 || dinh >= m.n);

			int bac = BacVao(m, dinh);

			cout << "Bac vao cua dinh " << dinh << " la: " << bac << endl;

			break;
		}
		case 15: {
			int dinh;
			do {
				cout << "Nhap dinh: ";
				cin >> dinh;
				if (dinh < 0 || dinh >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (dinh < 0 || dinh >= m.n);

			int bac = TinhBacRa(m, dinh);

			cout << "Bac ra cua dinh " << dinh << " la: " << bac << endl;

			break;
		}
		case 16: {
			VERTEX max = DinhBacMax(m);
			cout << "Dinh co bac lon nhat la: " << max << endl;
			break;
		}
		case 17: {
			VERTEX min = DinhBacMin(m);
			cout << "Dinh co bac lon nhat la: " << min << endl;
			break;
		}
		case 18: {
			VERTEX max = DinhBacMax(l);
			cout << "Dinh co bac lon nhat la: " << max << endl;
			break;
		}
		case 19: {
			VERTEX min = DinhBacMin(l);
			cout << "Dinh co bac nho nhat la: " << min << endl;
			break;
		}
		case 20: {
			VERTEX u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int kt = TimĐinhKe_BacMax(m, u, v);
			if (kt == 1) {
				cout << "Dinh ke co bac lon nhat voi dinh " << u << " la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 21: {
			VERTEX u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int kt = TimĐinhKe_BacMin(m, u, v);
			if (kt == 1) {
				cout << "Dinh ke co bac nho nhat voi dinh " << u << " la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 22: {
			VERTEX u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int kt = TimĐinhKe_BacMax(l, u, v);
			if (kt == 1) {
				cout << "Dinh ke co bac lon nhat voi dinh " << u << " la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 23: {
			VERTEX u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int kt = TimĐinhKe_BacMin(l, u, v);
			if (kt == 1) {
				cout << "Dinh ke co bac nho nhat voi dinh " << u << " la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 24: {
			Edge canhMax;
			int kt = TimCanhMax(m, canhMax);
			if (kt == 1) {
				cout << "Canh lon nhat trong do thi la: ";
				xuatCanh(canhMax);
			}
			else {
				cout << "Khong co canh trong do thi !" << endl;
			}

			break;
		}
		case 25: {
			Edge canhMin;
			int kt = TimCanhMin(m, canhMin);
			if (kt == 1) {
				cout << "Canh nho nhat trong do thi la: ";
				xuatCanh(canhMin);
			}
			else {
				cout << "Khong co canh trong do thi !" << endl;
			}

			break;
		}
		case 26: {
			Edge canhMax;
			int kt = TimCanhMax(l, canhMax);
			if (kt == 1) {
				cout << "Canh lon nhat trong do thi la: ";
				xuatCanh(canhMax);
			}
			else {
				cout << "Khong co canh trong do thi !" << endl;
			}
		}
		case 27: {
			Edge canhMin;
			int kt = TimCanhMin(l, canhMin);
			if (kt == 1) {
				cout << "Canh nho nhat trong do thi la: ";
				xuatCanh(canhMin);
			}
			else {
				cout << "Khong co canh trong do thi !" << endl;
			}

			break;
		}
		case 28: {
			int tongTS = TongTrongSo(m);
			cout << "Tong trong so cua cac canh la: " << tongTS << endl;
			break;
		}
		case 29: {
			int tongTS = TongTrongSo(l);
			cout << "Tong trong so cua cac canh la: " << tongTS << endl;
			break;
		}
		case 30: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int tongTS = TongTrongSoTuU(m, u);
			cout << "Tong trong so cac canh xuat phat tu " << u << " la: " << tongTS << endl;
			break;
		}
		case 31: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int tongTS = TongTrongSoVaoU(m, u);
			cout << "Tong trong so cac canh di vao " << u << " la: " << tongTS << endl;
			break;
		}
		case 32: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int tongTS = TongTrongSoTuU(l, u);
			cout << "Tong trong so cac canh xuat phat tu " << u << " la: " << tongTS << endl;
			break;
		}
		case 33: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int tongTS = TongTrongSoVaoU(l, u);
			cout << "Tong trong so cac canh di vao " << u << " la: " << tongTS << endl;
			break;
		}
		case 34: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			Edge c;
			int kt = CanhCoTrongSoLonNhat(m, u, c);

			if (kt == 1) {
				cout << "Canh co trong so lon nhat ke voi dinh " << u << " la: ";
				xuatCanh(c);
			}
			else {
				cout << "Khong co canh ke voi dinh " << u << endl;
			}
			break;
		}
		case 35: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			Edge c;
			int kt = CanhCoTrongSoLonNhat(l, u, c);

			if (kt == 1) {
				cout << "Canh co trong so lon nhat ke voi dinh " << u << " la: ";
				xuatCanh(c);
			}
			else {
				cout << "Khong co canh ke voi dinh " << u << endl;
			}
			break;
		}
		case 36: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			Edge c;
			int kt = CanhCoTrongSoNhoNhat(m, u, c);

			if (kt == 1) {
				cout << "Canh co trong so nho nhat ke voi dinh " << u << " la: ";
				xuatCanh(c);
			}
			else {
				cout << "Khong co canh ke voi dinh " << u << endl;
			}
			break;
		}
		case 37: {
			VERTEX u;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			Edge c;
			int kt = CanhCoTrongSoNhoNhat(l, u, c);

			if (kt == 1) {
				cout << "Canh co trong so nho nhat ke voi dinh " << u << " la: ";
				xuatCanh(c);
			}
			else {
				cout << "Khong co canh ke voi dinh " << u << endl;
			}
			break;
		}
		case 38: {
			int u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int kt = TimDinhke_MinTrongso(m, u, v);
			if (kt == 1) {
				cout << "Dinh ke voi dinh " << u << " co chi phi nho nhat la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 39: {
			int u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= m.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= m.n);

			int kt = TimDinhke_MaxTrongso(m, u, v);
			if (kt == 1) {
				cout << "Dinh ke voi dinh " << u << " co chi phi lon nhat la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 40: {
			int u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int kt = TimDinhke_MinTrongso(l, u, v);
			if (kt == 1) {
				cout << "Dinh ke voi dinh " << u << " co chi phi nho nhat la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		case 41: {
			int u, v;
			do {
				cout << "Nhap dinh: ";
				cin >> u;
				if (u < 0 || u >= l.n)
					cout << "Dinh khong hop le !" << endl;
			} while (u < 0 || u >= l.n);

			int kt = TimDinhke_MaxTrongso(l, u, v);
			if (kt == 1) {
				cout << "Dinh ke voi dinh " << u << " co chi phi lon nhat la: " << v << endl;
			}
			else
				cout << "Dinh " << u << " khong co dinh ke !" << endl;

			break;
		}
		default: {
			cout << "Lua chon khong hop le !" << endl;
		}
		}
		system("pause");
	}
}