// 20210304_Hero1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <ctime>


using namespace std;

/*
  실습.
  영웅은 절차적

  1) 텍스트로 진행되는 게임
  2) 게이미 시작되면 영웅의 이름과 난이도를 입력
  3) 난이도에 따라서 영웅의 HP / 만나게 되는 몬스터의 숫자가 변동
  4) 몬스터를 잡으면 랜덤하게 돈을 획득한다. ( 0 ~100 )
  5) 몬스터를 잡으면 던전을 계속 탐험할지 상점을 들를지 결정한다.
  6) 상점에 들르면 돈을 소모해서 HP를 회복할 수 있다.
  6_1) 보유금액에 따라 전체회복, +10, +20 +,30 차등회복
  7) HP가 0이 되면 게임오버
  8) 몬스터를 모두 잡으면 게임 클링

  0) 가위바위보 (비기면 승패가 정해질 때까지 반복) 패배 시 HP감소 승리 시 몬스터 처치) 순서도
  0_1) 졌을 때만 영웅 HP가 줄어든다.
  0_3) 몬스터는 한번 지면 바로 죽음

  탈출 게임 기반
  맵에 보이지 않는 몬스터가 존재

  ------------------------------------------
  1. 난이도 설정
  2. 맵 깔기 적 생성 , 플레이어 생성
  3. if: 적과 플레이어 좌표 == 적 좌표 -> 가위바위보 시작
  4. 결과에 따른 결과 (승리: 몬스터 삭제, 골드, 상점, 패배: 플레이어 이 전 좌표로 이동, 플레이어 HP 감소, 사망 시 게임 종료)
  5. 상점: 골드에 따라 HP 차등 회복 %로
  6. 최종 승리 시 승리 문구 깔아주기
*/

struct Player
{
	int HP;
	string name;
	int Gold;
};


int main()
{
	srand(time(NULL));

	string Easy = "Easy";
	string Normal = "Normal";
	string Hard = "Hard";
	cout << "난이도 설정" << endl << Easy << endl << Normal << endl << Hard << endl;
	string Level;
	cout << "정확하게 입력해주세요. 예시)Hard :";
	cin >> Level;
	int monATK = 10;
	Player Hero;
	cout << "세상을 구할 영웅! 당신의 이름은? : " << endl;
	cin >> Hero.name;
	int monValue;
	if (Level == Easy || Level == "EASY" || Level == "easy")
	{
		Hero.HP = 150;
		monValue = 3;
		Hero.Gold = 15;
	}
	else if (Level == Normal || Level == "NORMAL" || Level == "normal")
	{
		Hero.HP = 100;
		monValue = 5;
		Hero.Gold = 10;
	}
	else if (Level == Hard || Level == "HARD" || Level == "hard")
	{
		Hero.HP = 50;
		monValue = 7;
		Hero.Gold = 5;
	}
	int monY[6];
	int monX[6];

	int x;
	int y;
	//cin >> monValue;
	for (int i = 0; i < monValue;)
	{

		x = rand() % 10;
		y = rand() % 10;
		if (i == 0) {
			monX[i] = x;
			monY[i] = y;
			i++;
		}
		else if (i != 0)
		{
			if (monX[i - 1] != monX[i] && monY[i - 1] != monY[i]) {
				monX[i] = x;
				monY[i] = y;
				i++;
			}

		}

	}
	/*for (int k = 0; k < 7; k++) {
		cout << monY[k] << " " << monX[k] << endl;
	}*/


	char map[10][10] =
	{
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},
		{'*','*','*','*','*','*','*','*','*','*'},

	};


	map[0][0] = 'O';
	int enemyY[10];
	int enemyX[10];
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (b == monY[a] && j == monX[a])
				{

					map[b][j] = '*';

				}
			}
		}

	}


	for (int y = 0; y < 10; y++)
	{
		for (int u = 0; u < 10; u++)
		{
			cout << map[y][u];
		}
		cout << endl;
	}
	int m = 0;
	int n = 0;
	while (1)
	{
		if (Hero.HP == 0)
		{
			cout << Hero.name << "클리어는 다음 생에..." << endl << endl << endl << endl << endl << endl << endl << endl << endl;

			exit(1);
		}
		if (monValue == 0)
		{
			cout << Hero.name << "용사님... " << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << "겁나 힘들었다 ㄹㅇ 지금 몇시냐?";
			exit(1);
		}
		int battleOn = 0;
		//cout << endl << "한영 전환 중요합니다! 방향키 한글만 먹음!";
		int inputChar = _getch();
		inputChar = tolower(inputChar);
		//cout << inputChar;
		system("cls");
		cout << inputChar << endl;
		if (inputChar == 119 || inputChar == 184)//W
		{
			n = n - 1;
			if (n < 0)
			{
				n = n + 1;
			}
		}
		if (inputChar == 97 || inputChar == 177)//A
		{
			m = m - 1;
			if (m < 0)
			{
				m = m + 1;
			}
		}
		if (inputChar == 115 || inputChar == 164)//S
		{
			n = n + 1;
			if (n >= 10)
			{
				n = n - 1;
			}
		}
		if (inputChar == 100 || inputChar == 183)//D
		{

			m = m + 1;
			if (m >= 10)
			{
				m = m - 1;
			}
		}
		map[n][m] = 'R';
		for (int y = 0; y < 10; y++)
		{
			for (int u = 0; u < 10; u++)
			{
				if (inputChar == 119 || inputChar == 184)//W
				{
					map[n + 1][m] = '*';
					map[n][m] = 'T';

				}
				if (inputChar == 97 || inputChar == 177)//A
				{
					map[n][m + 1] = '*';
					map[n][m] = 'T';


				}
				if (inputChar == 115 || inputChar == 164)//S
				{
					map[n - 1][m] = '*';
					map[n][m] = 'T';


				}
				if (inputChar == 100 || inputChar == 183)//D
				{
					map[n][m - 1] = '*';
					map[n][m] = 'T';



				}
				cout << map[y][u];
			}
			cout << endl;
		}
		cout << "==========================================================================="
			<< endl << "용사의 남은 체력 : " << Hero.HP << endl
			<< endl << "보유 골드 : " << Hero.Gold << endl
			<< endl << "남은 몬스터 : " << monValue << endl

			<< "==========================================================================="
			<< endl;
		int Price;
		for (int x = 0; x < 10; x++)
		{
			cin.clear();
			Price = NULL;
			if ((n == monY[x] && m == monX[x]))
			{
				cin.clear();
				string com;
				string c;

				int number = (rand() % 3) + 1;
				if (number == 3)
				{
					com = "가위";
				}
				else if (number == 2)
				{
					com = "바위";
				}
				else if (number == 1)
				{
					com = "보";
				}
				cout << "야생의 몬스터를 만났다!" << endl << "**용사는 가위, 바위, 보 외에 다른 글자를 입력하면 패배 당합니다.**" << endl <<
					"===========================================================================" << endl;
				for (int i = 1; i > 0; i++)
				{
					{
						cin.clear();
						cout << "용사의 공격! : ";
						cin >> c;
						//cout << c << " 테스트용 " << endl;
						cout << "===========================================================================" << endl;
						if (c != "보" && c != "가위" && c != "바위")
						{
							cout << "패배!";
							Hero.HP = Hero.HP - 5;
							if (Hero.HP <= 0)
							{
								Hero.HP = 0;
							}
							map[n][m] = 'M';
							n = 0;
							m = 0;
							break;
						}
						else if (c == com)
						{
							cout << "무승부!";

						}
						else if (c == "가위" && com == "보")
						{
							cout << "용사 승!" << endl;
							Hero.Gold = Hero.Gold + 5;
							cout << "상점OPEN!" << "골드를 소모해 HP를 회복 하시겠습니까?" << endl << "보유 골드 : " << Hero.Gold << endl << "30골드 = 15 / 20골드 = 10 / 10골드 = 5" << endl << "가격 외 입력 시 상점 닫힘" << endl << "그리고 겜 터짐" << endl << ":";


							cin >> Price;
							if (Price == 30 && Hero.Gold >= 30)
							{
								Hero.Gold = Hero.Gold - 30;

								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 15;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 30 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 20 && Hero.Gold >= 20)
							{
								Hero.Gold = Hero.Gold - 20;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 10;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 20 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 10 && Hero.Gold >= 10)
							{
								Hero.Gold = Hero.Gold - 10;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 5;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 10 << endl
									<< "==========================================================================="
									<< endl;
							}
							else
							{
								cout << "상점을 이용하지 않습니다." << endl;
								Price = NULL;
							}
							cout << "당신의 여정에 행운이 있기를!" << endl;
							map[n][m] = 'T';
							monX[x] = 11;
							monY[x] = 11;
							monValue = monValue - 1;
							break;
						}
						else if (c == "바위" && com == "가위")
						{
							cout << "용사 승!" << endl;
							Hero.Gold = Hero.Gold + 5;
							cout << "상점OPEN!" << "골드를 소모해 HP를 회복 하시겠습니까?" << endl << "보유 골드 : " << Hero.Gold << endl << "30골드 = 15 / 20골드 = 10 / 10골드 = 5" << endl << "가격 외 입력 시 상점 닫힘" << endl << "그리고 겜 터짐" << endl << ":";
							//int Price;

							cin >> Price;
							if (Price == 30 && Hero.Gold >= 30)
							{
								Hero.Gold = Hero.Gold - 30;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 15;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 30 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 20 && Hero.Gold >= 20)
							{
								Hero.Gold = Hero.Gold - 20;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 10;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 20 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 10 && Hero.Gold >= 10)
							{
								Hero.Gold = Hero.Gold - 10;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 5;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 10 << endl
									<< "==========================================================================="
									<< endl;
							}
							else
							{
								cout << "상점을 이용하지 않습니다." << endl;
								Price = NULL;
							}
							cout << "당신의 여정에 행운이 있기를!" << endl;
							map[n][m] = 'T';
							monX[x] = 11;
							monY[x] = 11;
							monValue = monValue - 1;
							cin.clear();
							break;
						}
						else if (c == "보" && com == "바위")
						{
							cout << "용사 승!" << endl;
							Hero.Gold = Hero.Gold + 5;
							cout << "상점OPEN!" << "골드를 소모해 HP를 회복 하시겠습니까?" << endl << "보유 골드 : " << Hero.Gold << endl << "30골드 = 15 / 20골드 = 10 / 10골드 = 5" << endl << "가격 외 입력 시 상점 닫힘" << endl << "그리고 겜 터짐" << endl << ":";
							//int Price;

							cin >> Price;
							if (Price == 30 && Hero.Gold >= 30)
							{
								Hero.Gold = Hero.Gold - 30;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 15;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 30 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 20 && Hero.Gold >= 20)
							{
								Hero.Gold = Hero.Gold - 20;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 10;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 20 << endl
									<< "==========================================================================="
									<< endl;
							}
							else if (Price == 10 && Hero.Gold >= 10)
							{
								Hero.Gold = Hero.Gold - 10;
								if (Hero.Gold <= 0)
								{
									Hero.Gold = 0;
								}
								Hero.HP = Hero.HP + 5;
								cout << "==========================================================================="
									<< endl << "소모 골드 : " << 10 << endl
									<< "==========================================================================="
									<< endl;
							}
							else
							{
								cout << "상점을 이용하지 않습니다." << endl;
								Price = NULL;
							}
							cout << "당신의 여정에 행운이 있기를!" << endl;
							map[n][m] = 'T';
							monX[x] = 11;
							monY[x] = 11;
							monValue = monValue - 1;
							break;
						}
						else
						{
							cout << "패배!";
							Hero.HP = Hero.HP - 5;
							if (Hero.HP <= 0)
							{
								Hero.HP = 0;
							}
							map[n][m] = 'M';
							m = 0;
							n = 0;
							break;
						}
						cout << endl << "===========================================================================";
						cout << endl << "몬스터 : " << com << endl;
						cout << endl << "===========================================================================" << endl;
					}
				}
			}
		}




	}






}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
