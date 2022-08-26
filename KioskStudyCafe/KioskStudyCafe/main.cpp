// <���͵� ī�� Ű����ũ �����ϱ�>
//1. �ð��̿�� ���� - �ð��� 2000�� pay
//2. �¼� �����ϱ�
//3. �繰��
//4. ī�� �̿� or �̿� X (�̿��ϸ� ��� ���տ� �ݾ� �߰�)
//5. �̺�Ʈ - �ڵ��ȣ ���߸� 10% ����
//6. �¼� ����
//7. ����Ȯ�� - �� ���� �����ֱ�

#include <iostream>
using namespace std;
//����� �����Է�
class Member {
public:
	string memname, phone;
	int time = 0, timepay = 2000;

	void Makemember(Member member) {
		cout << "�̸��� �Է��Ͻÿ� : "; cin >> memname;
		cout << "��ȣ�� �Է��Ͻÿ� : "; cin >> phone;
		cout << "��� �ð��� �Է��Ͻÿ�(�ð� �� 2000��) : "; cin >> time;
	}

	void Countpay(Member member, int& total) {
		total = member.time * member.timepay;
	}
	void showMember(Member member, int& total) {
		cout << "�̸� : " << memname << endl;
		cout << "��ȣ : " << phone << endl;
		cout << "��� �ð� : " << time << endl;
	}
};

//����� �繰�� �̿� ������ ���� �繰�� class
class Locker {
public:

	struct LockerManage {
		bool** seats;
		int reserved;
	};
	LockerManage* locermanager = NULL;

	void makeLocker() {

		locermanager = new LockerManage[1];
		for (int i = 0; i < 1; i++) {
			locermanager[i].seats = new bool* [10];
			for (int j = 0; j < 10; j++) {
				locermanager[i].seats[j] = new bool[8];
				for (int k = 0; k < 8; k++) {
					locermanager[i].seats[j][k] = false;
				}
			}
			locermanager[i].reserved = 0;
		}

	}
	void showLocker() {
		cout << ">>>>>> �繰�� <<<<<<<" << endl;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				printf("%c : ", 'A' + j);
				for (int k = 0; k < 8; k++)
				{
					if (locermanager[i].seats[j][k] == false)
						cout << "��";
					else
						cout << "��";
				}
				cout << endl;
			}
		}
	}

	void reserved(int& total) {
		int low, col;
		int box = 5000;//�繰�� �ϳ� �� ����
		cout << "�繰�� ���� (0�� 0�� �Է��ϸ� ����)" << endl;
		while (1) {
			cout << "����ϰ� ���� �繰�� ��ȣ �Է� : "; cin >> low >> col;
			if (low == 0 || col == 0)break;
			else {
				for (int i = 0; i < 1; i++) {
					locermanager[i].seats[low - 1][col - 1] = true;
				}
			}
		}
		total = total + box;//�繰�� �ݾ� �߰�
	}
};

//�¼��� ���� class - �¼��� �����ְ� ����ڰ� ���� ���� �Է��Ͽ� �¼��� ������ �� ������, ������ �¼��� ������
class SeatMenu {
public:
	struct Room {
		string roomtitle;
		string roomgenre;
	};
	struct Seat {
		string seatinfor;
		int line;
		int seatnum;
	};
	Room room;
	Seat seat;
	struct Roomtime {
		string title, name;//roomtitle, seatinfor
		string seattime;//seatinfor ���� ��� �ɴ��� ���� (�¼�����)
		bool** seats;
		int reserved;
	};

	Roomtime* schedule = NULL;

	int makeSchedule(Room room, Seat seat, int& count) {
		schedule = new Roomtime[count];

		for (int i = 0; i < count; i++) {
			schedule[i].title = room.roomtitle;
			schedule[i].name = seat.seatinfor;
			schedule[0].seattime = "openseat";//������ �¼�
			schedule[1].seattime = "notebookseat";//��Ʈ�� ��� ���� �¼�
			schedule[2].seattime = "aloneseat";//ĭ���� �ִ� 1�� �¼�
			schedule[i].seats = new bool* [seat.line];
			for (int j = 0; j < seat.line; j++) {
				schedule[i].seats[j] = new bool[seat.seatnum];
				for (int k = 0; k < seat.seatnum; k++) {
					schedule[i].seats[j][k] = false;
				}
			}
			schedule[i].reserved = 0;
		}
		return count;
	}
	void showSchedule(Room room, Seat seat, int& count) {
		cout << endl;
		cout << ">>>>>>> ���͵�ī�� �¼� ��ȸ <<<<<<<" << endl;
		cout << room.roomtitle << endl;
		for (int i = 0; i < count; i++) {
			cout << schedule[i].seattime << endl;
			for (int j = 0; j < seat.line; j++) {
				printf("%c : ", 'A' + j);
				for (int k = 0; k < seat.seatnum; k++) {
					if (schedule[i].seats[j][k] == false)
						cout << "��";
					else
						cout << "��";
				}
				cout << endl;
			}
		}
	}
	void Studyreserved(int& count) {
		string cseat;
		int low, col;
		cout << endl;
		cout << " > * ���͵�ī�� �¼� �����ϱ� * < " << endl;
		cout << "��� �� �¼��� ���� ���� : "; cin >> cseat;
		while (1) {
			cout << "�¼� ���� (0�� 0���� �Է��ϸ� �¼����� ����) : "; cin >> low >> col;
			if (low == 0 || col == 0)break;
			else {
				for (int i = 0; i < count; i++) {
					if (cseat == schedule[i].seattime) {
						schedule[i].seats[low - 1][col - 1] = true;
					}
				}
			}
		}
	}

	void deleteschedule(Room room, Seat seat, int& count) {//�¼��� �ٲܶ��� ���� ���� �¼� �ʱ�ȭ �Լ�
		for (int i = 0; i < count; i++) {
			schedule[i].seattime;
			for (int j = 0; j < seat.line; j++) {
				for (int k = 0; k < seat.seatnum; k++) {
					schedule[i].seats[j][k] = { };
				}
			}
		}
	}

	void Moveschedule(Room room, Seat seat, int& count) {//�¼� �ű�� �Լ�
		string moveroom;//�ű� �¼����� �Է�
		int galo, sealo;

		cout << endl;
		cout << " > *�¼� �����ϱ� * < " << endl;
		cout << "�ű� �¼��� ���� �Է� : ";  cin >> moveroom;
		while (1) {
			cout << "�¼� ���� (0�� 0���� �Է��ϸ� �¼� ���� ����) : "; cin >> galo >> sealo;
			if (galo == 0 || sealo == 0)break;
			else {
				for (int i = 0; i < count; i++) {
					if (moveroom == schedule[i].seattime) {
						schedule[i].seats[galo - 1][sealo - 1] = true;
					}
				}
			}
		}

	}
};
//ī�� class
class Cafe {
public:
	void CafeMenu(int& total) {
		string coffe[6] = { "�Ƹ޸�ī��","������", "��纣��������", "ī���", "����������", "īǪġ��" };
		int price[6] = { 2200, 2500, 3800, 2500, 1800, 3000 };
		cout << "---------------CAFE MENU-------------" << endl;;
		for (int i = 0; i < 6; i++) {
			cout << i + 1 << "." << coffe[i] << " " << price[i] << "��\n";
		}
		short order[6], qty[6];
		int cnt = 0;
		cout << endl;
		cout << "--------------�ֹ��ϱ�-------------" << endl;
		while (true) {
			char n;
			cout << "��ȣ : "; cin >> order[cnt];
			cout << "���� : "; cin >> qty[cnt++];
			cout << "����(y / n) ? : "; cin >> n;
			if (n == 'n' || n == 'N') break;
		}
		cout << endl;
		cout << "--------------�ֹ����--------------" << endl;
		for (int i = 0; i < cnt; i++) {
			cout << coffe[order[i] - 1] << " : " << qty[i] << "�� * ";
			cout << price[order[i] - 1] << "�� = ";
			cout << qty[i] * price[order[i] - 1] << "��\n";
			total += qty[i] * price[order[i] - 1];
		}
		cout << "�� �ݾ� : " << total << "���Դϴ�.\n";
		cout << endl;
	}
};
//�̺�Ʈ class
class EventMenu {
public:
	void Event(int& total) {
		int event = 1004; //�̺�Ʈ ��÷ ��ȣ
		int userevent;
		cout << "----------------�̺�Ʈ â---------------" << endl;
		cout << "���� ��ȣ�� �Է��Ͻÿ� : "; cin >> userevent;
		bool found = false;
		if (userevent == event) {
			found = true;
			cout << "���� �����Դϴ�. (��ü �ݾ׿��� 10% ����)" << endl;
			total = total - total * 0.1;
			cout << "�� �ݾ� : " << total << "���Դϴ�\n";
		}
		else {
			cout << "���� ���� ������ȣ �Դϴ�." << endl;
			cout << "�� �ݾ� : " << total << "���Դϴ�.\n";
		}
	}
};
int main() {
	Locker lock;
	Member member;
	SeatMenu seatmenu;
	seatmenu.room;
	seatmenu.seat;
	EventMenu evt;
	Cafe cafe;
	int count = 3;
	int total = 0;
	int menu;

	seatmenu.room.roomtitle = "-------���͵� ī�� �¼�--------";
	cout << endl;
	seatmenu.room.roomgenre = "��ǻ��, ����, ������";
	seatmenu.seat.seatinfor = "���͵� ī�� �¼��� ����";
	seatmenu.seat.line = 8;
	seatmenu.seat.seatnum = 12;

	do {//switch���� �̿��Ͽ� �Լ� ����
		cout << "*************** STUDY CAFE ****************\n";
		cout << "1) �̿�� ����\n";
		cout << "2) �¼� ����\n";
		cout << "3) �繰�� ����\n";
		cout << "4) �ڸ� �̵�\n";
		cout << "5) ī��\n";
		cout << "6) �̺�Ʈ\n";
		cout << "7) ���� Ȯ��\n";
		cout << "0) ���α׷� ����\n";
		cout << "********************************************\n";
		cout << "�޴� �Է�: "; cin >> menu;

		switch (menu) {
		case 1://�����Է� �� ��� �ð� �����ϱ� 
			member.Makemember(member);
			member.Countpay(member, total);
			cout << "�� �ݾ��� " << total << "���Դϴ�.\n";
			break;

		case 2://�¼� ����
			count = seatmenu.makeSchedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.Studyreserved(count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			break;

		case 3://�繰�� �̿��
			lock.makeLocker();
			lock.showLocker();
			lock.reserved(total);
			lock.showLocker();
			break;

		case 4:// �ڸ��̵� ����
			seatmenu.deleteschedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.Moveschedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			break;

		case 5:// ī�� �̿� ����
			cafe.CafeMenu(total);
			break;

		case 6:// �̺�Ʈ ���� - �ڵ� ���߸� �� �ݾ׿��� 10%����
			evt.Event(total);
			break;

		case 7:// ���� Ȯ�� - �¼������ְ�, ī�伱���Ѱź����ְ� �ѱݾ� �����ֱ�
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			member.showMember(member, total);
			cout << total << "���Դϴ�.\n";
			break;

		case 0: cout << "���α׷��� �����մϴ�.\n"; break;
		}
	} while (menu != 0);
}