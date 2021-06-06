//
// Created by WaiWaiXi on 2021/5/21.
//

#include <iomanip>
#include "GameBoard.h"

GameBoard::GameBoard() = default;

// 游戏流程控制
void GameBoard::start() {
    cout << "请选择模式" << endl;
    cout << "1:单人模式" << endl;
    cout << "2:双人模式" << endl;
    cout << "请输入对应的模式序号" << endl;
    while (true) {
        string mode;
        cin >> mode;
        if (mode == "1") {
            string name;
            players_init(1);
            playerNumber = 1;
            cout << "请输入玩家名称：" << endl;
            cin >> name;
            players[0].name = name;
            break;
        } else if (mode == "2") {
            string name;
            players_init(2);
            playerNumber = 2;
            cout << "请玩家一输入名称:" << endl;
            cin >> name;
            players[0].name = name;
            cout << "请玩家二输入名称:" << endl;
            cin >> name;
            players[1].name = name;
            break;
        } else {
            cout << "请输入1或2来选择模式" << endl;
        }
    }
    cout << "游戏开始！输入 w z a s 表示上下左右，回车确定" << endl;
    generate_node();
    print_board();
    while (true) {
        print_player(players, turn);

        // 如果需要检测cheat就检测棋盘状态
        if (cheat.need_detect(turn)) {
            int can_number = 0;
            char can_direction;
            if (can_play(board, 'w')) {
                can_number++;
                can_direction = 'w';
            }
            if (can_play(board, 'z')) {
                can_number++;
                can_direction = 'z';
            }
            if (can_play(board, 'a')) {
                can_number++;
                can_direction = 'a';
            }
            if (can_play(board, 's')) {
                can_number++;
                can_direction = 's';
            }
            if (can_number == 1) {
                // 说明只能往一个方向移动，启动cheat
                cout << cheat.content << " 同意请输入" << can_direction << endl;
                cheat.do_cheat();
            }
        }
        string instruction;
        cin >> instruction;
        if (instruction == "w" or instruction == "z" or instruction == "a" or instruction == "s") {
            vector<vector<int>> origin_board = board;
            int origin_score = players[turn].score;
            board = play(board, instruction[0], true);
            bool is_changed = is_different(origin_board, board);
            if (is_changed) {// 操作有效,产生新数组、判断游戏结束、更换玩家、生成日志
                generate_node();
                if (is_over()) { break; }
                print_score(players, turn);

                // 日志,在有得分的时候进行输出
                int changed_score = players[turn].score - origin_score;
                if (log_mode && changed_score > 0) {
                    log_motivation.log(players[turn].name, instruction, changed_score);
                }

                turn = (turn + 1) % playerNumber;// 更换玩家
            } else {
                cout << "无效操作，请重试" << endl;
            }
        } else if (playerNumber > 1 && cheat.can_cheat() && instruction == "c") {// cheat设置
            string cheat_content;
            cin >> cheat_content;
            cheat.set_cheat(cheat_content, turn);
        } else {
            cout << "无效输入，输入 w z a s 表示上下左右，回车确定" << endl;
        }
        print_board();
    }

    // 游戏结束处理
    log_motivation.close();
    print_board();
    int max_score = 0;
    for (const auto &item : players) {
        cout << item.name << "最终分数为：" << item.score << endl;
        max_score = max(max_score, item.score);
    }
    if (playerNumber > 1) {
        int winner_number = 0;
        cout << "胜利者为：";
        for (const auto &item : players) {
            if (item.score == max_score) {
                winner_number++;
                if (winner_number > 1) {
                    cout << "，" << item.name;
                } else {
                    cout << item.name;
                }
            }
        }
        if (winner_number > 1) {
            cout << " 打成平局" << endl;
        } else {
            cout << endl;
        }
    }
    cout << "最大数字达到" << node_max << "，游戏结束！" << endl;
}

void GameBoard::test_mode_on() {
    this->test_mode = true;
}

void GameBoard::board_init(int size) {
    boardSize = size;
    this->board.resize(size);
    for (auto &item : board) {
        item.resize(size);
        for (auto &number : item)
            number = 0;
    }
}

void GameBoard::players_init(int size) {
    this->playerNumber = size;
    this->players = vector<Player>(size);
}

vector<int> GameBoard::generate_node() {
    if (this->node_num == this->boardSize * this->boardSize) {
        cout << "棋盘满了，不应该再生成新数字！" << endl;
        return {-1, -1};
    }
    srand(time(nullptr));
    while (true) {
        int row = rand() % this->boardSize;
        int col = rand() % this->boardSize;
        if (this->board[row][col] == 0) {
            this->board[row][col] = 2;
            this->node_num++;
            return {row, col};
        }
    }
}

bool GameBoard::is_over() {
    if (test_mode) {
        if (node_max >= test_max_node) {
            return true;
        }
    }
    if (node_num < boardSize * boardSize) {
        return false;
    }
    vector<char> directions = {'w', 'z', 'a', 's'};
    for (const auto &item : directions) {
        if (!can_play(board, item)) {
            return true;
        }
    }
    return false;
}

void GameBoard::print_player(vector<Player> players, int turn) {
    Player player = players[turn];
    cout << "请玩家：" << player.name << " 操作" << endl;
}


void GameBoard::print_board() {
    char split = '|';
    string border = "+";

    for (int i = 0; i < boardSize; i++) {
        border.append("-----+");
    }
    for (int i = 0; i < boardSize; i++) {
        cout << border << endl;
        for (int j = 0; j < boardSize; j++) {
            cout << split << setw(5) << board[i][j];
        }
        cout << split << endl;
    }
    cout << border << endl;
}

void GameBoard::print_score(vector<Player> players, int turn) {
    Player player = players[turn];
    cout << "玩家：" << player.name << " 现在分数：" << player.score << endl;
}

vector<vector<int>> GameBoard::move(vector<vector<int>> origin_board, char direction) {
    switch (direction) {
        case 'w':
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = move_left(origin_board);
            origin_board = rotate(origin_board);
            break;
        case 'z':
            origin_board = rotate(origin_board);
            origin_board = move_left(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            break;
        case 'a':
            origin_board = move_left(origin_board);
            break;
        case 's':
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = move_left(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            break;
        default:
            cout << "move函数接受的方向参数不是w z a s" << endl;
    }
    return origin_board;
}

vector<vector<int>> GameBoard::move_left(vector<vector<int>> origin_board) {
    for (auto &i : origin_board) {
        i = move_line_left(i);
    }
    return origin_board;
}

vector<int> GameBoard::move_line_left(vector<int> origin_line) {
    int currIndex = 0;
    for (const auto &item : origin_line) {
        if (item != 0) {
            origin_line[currIndex] = item;
            currIndex++;
        }
    }
    for (int i = currIndex; i < origin_line.size(); ++i) {
        origin_line[i] = 0;
    }
    return origin_line;
}

vector<vector<int>> GameBoard::rotate(vector<vector<int>> origin_board) {
    int size = origin_board.size();
    vector<vector<int>> result_board;
    result_board.resize(size);
    for (auto &item : result_board) {
        item.resize(size);
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result_board[j][size - 1 - i] = origin_board[i][j];
        }
    }
    return result_board;
}

vector<vector<int>> GameBoard::merge(vector<vector<int>> origin_board, char direction, bool real) {
    switch (direction) {
        case 'w':
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = merge_left(origin_board, real);
            origin_board = rotate(origin_board);
            break;
        case 'z':
            origin_board = rotate(origin_board);
            origin_board = merge_left(origin_board, real);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            break;
        case 'a':
            origin_board = merge_left(origin_board, real);
            break;
        case 's':
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            origin_board = merge_left(origin_board, real);
            origin_board = rotate(origin_board);
            origin_board = rotate(origin_board);
            break;
        default:
            cout << "move函数接受的方向参数不是w z a s" << endl;
    }
    return origin_board;
}


vector<vector<int>> GameBoard::merge_left(vector<vector<int>> origin_board, bool real) {
    for (auto &item : origin_board) {
        item = merge_line_left(item, real);
    }
    return origin_board;
}

vector<int> GameBoard::merge_line_left(vector<int> origin_line, bool real) {
    int pre = origin_line[0];
    for (int i = 1; i < origin_line.size(); ++i) {
        if (pre != 0 && origin_line[i] == pre) { // 找到合并对象
            origin_line[i - 1] *= 2;
            origin_line[i] = 0;
            pre = 0;
            if (real) {
                this->players[this->turn].score += origin_line[i - 1];
                this->node_num--;
                this->node_max = node_max > origin_line[i - 1] ? node_max : origin_line[i - 1];
            }
        } else {
            pre = origin_line[i];
        }
    }
    return origin_line;
}

bool GameBoard::is_different(vector<vector<int>> board_i, vector<vector<int>> board_j) {
    for (int i = 0; i < board_i.size(); ++i) {
        for (int j = 0; j < board_i.size(); ++j) {
            if (board_i[i][j] != board_j[i][j]) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> GameBoard::play(vector<vector<int>> origin_board, char direction, bool real) {
    origin_board = move(origin_board, direction);
    origin_board = merge(origin_board, direction, real);
    origin_board = move(origin_board, direction);
    return origin_board;
}

bool GameBoard::can_play(const vector<vector<int>> &origin_board, char direction) {
    vector<vector<int>> new_board = play(origin_board, direction, false);
    return is_different(new_board, origin_board);
}


void GameBoard::test(const string &in_name, const string &out_name) {
    ifstream fin(in_name);
    string line;
    getline(fin, line);
    int size = line[0] - '0';
    vector<vector<int>> test_board((int) size);

    // 从文件中读入棋盘
    for (int i = 0; i < size; ++i) {
        getline(fin, line);
        vector<int> board_line(size);
        for (int j = 0; j < size; ++j) {
            board_line[j] = line[2 * j] - '0';
        }
        test_board[i] = board_line;
    }

    players_init(1);
    board_init(size);
    board = test_board;

    // 从文件中读入指令
    getline(fin, line);
    char direction = line[0];

    int can_number = 0;
    bool can_w = can_play(test_board, 'w');
    bool can_a = can_play(test_board, 'a');
    bool can_s = can_play(test_board, 's');
    bool can_z = can_play(test_board, 'z');
    if (can_w) { can_number++; }
    if (can_a) { can_number++; }
    if (can_s) { can_number++; }
    if (can_z) { can_number++; }

    board = play(test_board, direction, true);
    int score_change = players[0].score;

    ofstream out(out_name);
    out << can_number;
    if (can_w) { out << " w"; }
    if (can_a) { out << " a"; }
    if (can_s) { out << " s"; }
    if (can_z) { out << " z"; }
    out << endl;

    for (const auto &item :board) {
        out << item[0];
        for (int i = 1; i < item.size(); ++i) {
            out << ' ' << item[i];
        }
        out << endl;
    }

    // 接下来进行随机生成
    vector<int> location = generate_node();
    out << 2 << endl;
    out << location[0] << ' ' << location[1] << endl;
    out << score_change << endl;
    out.close();
    fin.close();
}

void GameBoard::log_mode_on() {
    this->log_motivation = Log("motivation_log.txt", "移动得分：");
    this->log_mode = true;
}

