#include<stdio.h>
#include<string.h>
#include<ctype.h>

enum modules[PASSWORD, COMPLICATED, SEQUENCE, WIRES];

char* words[] = {
    "about", "after", "again", "below", "could", "every", "first",
    "found", "great", "house", "large", "learn", "never", "other",
    "place", "plant", "point", "right", "small", "sound", "spell",
    "still", "study", "their", "there", "these", "thing", "think",
    "three", "water", "where", "which", "world", "would", "write" };

char opr[] = {'C', 'D', 'C', 'B', 'S', 'P', 'D', 'P', 'S', 'B', 'C', 'B', 'S', 'S', 'P', 'D'};

void clear() {
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

int valid_pass(char* s) {
    if (strlen(s) != 6)
        return 0;
    int i = 0;
    for (i = 0; i < 6; i++) {
        if (!isalpha(s[i]))
            return 0;
        s[i] = tolower(s[i]);
    }

    return 1;
}

void password() {
    printf("\n【密码模块】\n");
    printf("输入：位置 备选字母【例：1 clqkro】\n");
    printf("输入 0 重新筛选；输入 # 退出密码模块\n\n");

    char c, sign[36];
    memset(sign, -1, sizeof(sign));
    while (1) {
        while (isspace(c = getchar()));
        if (c == '#') {
            clear();
            break;
        }

        if (c == '0') {
            memset(sign, -1, sizeof(sign));
            clear();
            printf("本轮结束\n\n");
            continue;
        }

        if (c >= '1' && c <= '5') {
            char letters[10];
            scanf("%s", letters);
            if (!valid_pass(letters)) {
                clear();
                printf("invalid input\n");
                continue;
            }
            c -= '1';
//            printf("pos: %d, input: %s\n", c, letters);

            int i, j;
            for (i = 0; i < 35; i++) {
                if (sign[i] == 0) continue;
                sign[i] = 0;
                for (j = 0; j < strlen(letters); j++) {
                    if (words[i][c] == letters[j]) {
                        sign[i] = 1;
                        printf("%s ", words[i]);
                        break;
                    }
                }
            }
            printf("\n");
        } else {
            clear();
            printf("invalid input\n");
            continue;
        }
    }

}

int valid_comp(char* s) {
    if (strlen(s) > 4) return 0;

    char sign[5] = {0};
    int i;
    for (i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
        switch(s[i]) {
            case 'b':
                sign[0]++;
                break;
            case 'r':
                sign[1]++;
                break;
            case 's':
                sign[2]++;
                break;
            case 'l':
                sign[3]++;
                break;
            case 'x':
                sign[4]++;
                break;
            default:
                return 0;
        }
    }

    for (i = 0; i < 5; i++) {
        if (sign[i] > 1) return 0;
    }

    return 1;
}

void complex() {
    printf("\n【复杂线路模块】\n");
    printf(
        "C 剪断线路\n"
        "D 不要剪断线路\n"
        "S 如果炸弹序列号末位为偶数则剪断线路\n"
        "P 如果炸弹有 Parallel 端口则剪断线路\n"
        "B 如果炸弹上有两个或更多电池则剪断线路\n\n");
    printf("输入：带蓝色 B；带红色 R；带星 S；带灯 L；四种均无 X【例：蓝白线带星星：BS】\n");
    printf("注：可以一次输入多个；BRSL 无顺序；大小写不敏感\n");
    printf("输入 # 退出复杂线路模块\n\n");

    while (1) {
        int mod = 0;
        char appear[10];
        scanf("%s", appear);

        if (strcmp(appear, "#") == 0) {
            clear();
            break;
        }

        if (!valid_comp(appear)) {
            clear();
            printf("invalid input\n");
            continue;
        }

        int i;
        for (i = 0; i < strlen(appear); i++) {
            switch(appear[i]) {
                case 'r':
                    mod += 8;
                    break;
                case 'b':
                    mod += 4;
                    break;
                case 's':
                    mod += 2;
                    break;
                case 'l':
                    mod += 1;
                    break;
                case 'x':
                    break;
            }
        }

       printf("%c ", opr[mod]);
    }

}

int main() {
    printf("拆弹辅助器 | 2020.3.28 v1.0 | skuld\n\n");
    while (1) {
        printf("\n——————————————\n");
        printf("输入：1 密码模块；2 复杂线路模块；# 退出\n");
        char c;
        while ((c = getchar()) != '#' && !(c >= '1' && c <= '2'));

        if ( c == '#') break;

        switch(c) {
            case '1':
                password();
                break;
            case '2':
                complex();
                break;
        }
    }

    return 0;
}
