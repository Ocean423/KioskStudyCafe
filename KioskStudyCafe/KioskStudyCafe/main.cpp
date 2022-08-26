// <스터디 카페 키오스크 구현하기>
//1. 시간이용권 끊기 - 시간당 2000원 pay
//2. 좌석 선택하기
//3. 사물함
//4. 카페 이용 or 이용 X (이용하면 요금 총합에 금액 추가)
//5. 이벤트 - 코드번호 맞추면 10% 할인
//6. 좌석 변경
//7. 정보확인 - 총 정보 보여주기

#include <iostream>
using namespace std;
//사용자 정보입력
class Member {
public:
	string memname, phone;
	int time = 0, timepay = 2000;

	void Makemember(Member member) {
		cout << "이름을 입력하시오 : "; cin >> memname;
		cout << "번호를 입력하시오 : "; cin >> phone;
		cout << "사용 시간을 입력하시오(시간 당 2000원) : "; cin >> time;
	}

	void Countpay(Member member, int& total) {
		total = member.time * member.timepay;
	}
	void showMember(Member member, int& total) {
		cout << "이름 : " << memname << endl;
		cout << "번호 : " << phone << endl;
		cout << "사용 시간 : " << time << endl;
	}
};

//사용자 사물함 이용 유무에 따른 사물함 class
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
		cout << ">>>>>> 사물함 <<<<<<<" << endl;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				printf("%c : ", 'A' + j);
				for (int k = 0; k < 8; k++)
				{
					if (locermanager[i].seats[j][k] == false)
						cout << "□";
					else
						cout << "■";
				}
				cout << endl;
			}
		}
	}

	void reserved(int& total) {
		int low, col;
		int box = 5000;//사물함 하나 당 가격
		cout << "사물함 예약 (0행 0열 입력하면 종료)" << endl;
		while (1) {
			cout << "사용하고 싶은 사물함 번호 입력 : "; cin >> low >> col;
			if (low == 0 || col == 0)break;
			else {
				for (int i = 0; i < 1; i++) {
					locermanager[i].seats[low - 1][col - 1] = true;
				}
			}
		}
		total = total + box;//사물함 금액 추가
	}
};

//좌석에 대한 class - 좌석을 보여주고 사용자가 열과 행을 입력하여 좌석을 선택할 수 있으며, 선택한 좌석을 보여줌
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
		string seattime;//seatinfor 내가 어디에 앉는지 종류 (좌석종류)
		bool** seats;
		int reserved;
	};

	Roomtime* schedule = NULL;

	int makeSchedule(Room room, Seat seat, int& count) {
		schedule = new Roomtime[count];

		for (int i = 0; i < count; i++) {
			schedule[i].title = room.roomtitle;
			schedule[i].name = seat.seatinfor;
			schedule[0].seattime = "openseat";//개방형 좌석
			schedule[1].seattime = "notebookseat";//노트북 사용 가능 좌석
			schedule[2].seattime = "aloneseat";//칸막이 있는 1인 좌석
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
		cout << ">>>>>>> 스터디카페 좌석 조회 <<<<<<<" << endl;
		cout << room.roomtitle << endl;
		for (int i = 0; i < count; i++) {
			cout << schedule[i].seattime << endl;
			for (int j = 0; j < seat.line; j++) {
				printf("%c : ", 'A' + j);
				for (int k = 0; k < seat.seatnum; k++) {
					if (schedule[i].seats[j][k] == false)
						cout << "□";
					else
						cout << "■";
				}
				cout << endl;
			}
		}
	}
	void Studyreserved(int& count) {
		string cseat;
		int low, col;
		cout << endl;
		cout << " > * 스터디카페 좌석 선택하기 * < " << endl;
		cout << "사용 할 좌석의 종류 선택 : "; cin >> cseat;
		while (1) {
			cout << "좌석 선택 (0행 0열을 입력하면 좌석선택 종료) : "; cin >> low >> col;
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

	void deleteschedule(Room room, Seat seat, int& count) {//좌석을 바꿀때를 위해 만든 좌석 초기화 함수
		for (int i = 0; i < count; i++) {
			schedule[i].seattime;
			for (int j = 0; j < seat.line; j++) {
				for (int k = 0; k < seat.seatnum; k++) {
					schedule[i].seats[j][k] = { };
				}
			}
		}
	}

	void Moveschedule(Room room, Seat seat, int& count) {//좌석 옮기는 함수
		string moveroom;//옮길 좌석종류 입력
		int galo, sealo;

		cout << endl;
		cout << " > *좌석 변경하기 * < " << endl;
		cout << "옮길 좌석의 종류 입력 : ";  cin >> moveroom;
		while (1) {
			cout << "좌석 선택 (0행 0열을 입력하면 좌석 선택 종료) : "; cin >> galo >> sealo;
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
//카페 class
class Cafe {
public:
	void CafeMenu(int& total) {
		string coffe[6] = { "아메리카노","핫초코", "블루베리스무디", "카페라떼", "에소프레소", "카푸치노" };
		int price[6] = { 2200, 2500, 3800, 2500, 1800, 3000 };
		cout << "---------------CAFE MENU-------------" << endl;;
		for (int i = 0; i < 6; i++) {
			cout << i + 1 << "." << coffe[i] << " " << price[i] << "원\n";
		}
		short order[6], qty[6];
		int cnt = 0;
		cout << endl;
		cout << "--------------주문하기-------------" << endl;
		while (true) {
			char n;
			cout << "번호 : "; cin >> order[cnt];
			cout << "수량 : "; cin >> qty[cnt++];
			cout << "다음(y / n) ? : "; cin >> n;
			if (n == 'n' || n == 'N') break;
		}
		cout << endl;
		cout << "--------------주문결과--------------" << endl;
		for (int i = 0; i < cnt; i++) {
			cout << coffe[order[i] - 1] << " : " << qty[i] << "개 * ";
			cout << price[order[i] - 1] << "원 = ";
			cout << qty[i] * price[order[i] - 1] << "원\n";
			total += qty[i] * price[order[i] - 1];
		}
		cout << "총 금액 : " << total << "원입니다.\n";
		cout << endl;
	}
};
//이벤트 class
class EventMenu {
public:
	void Event(int& total) {
		int event = 1004; //이벤트 당첨 번호
		int userevent;
		cout << "----------------이벤트 창---------------" << endl;
		cout << "쿠폰 번호를 입력하시오 : "; cin >> userevent;
		bool found = false;
		if (userevent == event) {
			found = true;
			cout << "옳은 쿠폰입니다. (전체 금액에서 10% 할인)" << endl;
			total = total - total * 0.1;
			cout << "총 금액 : " << total << "원입니다\n";
		}
		else {
			cout << "옳지 않은 쿠폰번호 입니다." << endl;
			cout << "총 금액 : " << total << "원입니다.\n";
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

	seatmenu.room.roomtitle = "-------스터디 카페 좌석--------";
	cout << endl;
	seatmenu.room.roomgenre = "컴퓨터, 오픈, 독서실";
	seatmenu.seat.seatinfor = "스터디 카페 좌석의 종류";
	seatmenu.seat.line = 8;
	seatmenu.seat.seatnum = 12;

	do {//switch문을 이용하여 함수 실행
		cout << "*************** STUDY CAFE ****************\n";
		cout << "1) 이용권 선택\n";
		cout << "2) 좌석 선택\n";
		cout << "3) 사물함 선택\n";
		cout << "4) 자리 이동\n";
		cout << "5) 카페\n";
		cout << "6) 이벤트\n";
		cout << "7) 정보 확인\n";
		cout << "0) 프로그램 종료\n";
		cout << "********************************************\n";
		cout << "메뉴 입력: "; cin >> menu;

		switch (menu) {
		case 1://정보입력 및 사용 시간 선택하기 
			member.Makemember(member);
			member.Countpay(member, total);
			cout << "총 금액은 " << total << "원입니다.\n";
			break;

		case 2://좌석 선택
			count = seatmenu.makeSchedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.Studyreserved(count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			break;

		case 3://사물함 이용권
			lock.makeLocker();
			lock.showLocker();
			lock.reserved(total);
			lock.showLocker();
			break;

		case 4:// 자리이동 유무
			seatmenu.deleteschedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.Moveschedule(seatmenu.room, seatmenu.seat, count);
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			break;

		case 5:// 카페 이용 유무
			cafe.CafeMenu(total);
			break;

		case 6:// 이벤트 유무 - 코드 맞추면 총 금액에서 10%할인
			evt.Event(total);
			break;

		case 7:// 정보 확인 - 좌석보여주고, 카페선택한거보여주고 총금액 보여주기
			seatmenu.showSchedule(seatmenu.room, seatmenu.seat, count);
			member.showMember(member, total);
			cout << total << "원입니다.\n";
			break;

		case 0: cout << "프로그램을 종료합니다.\n"; break;
		}
	} while (menu != 0);
}