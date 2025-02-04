void save_player_data(const char *username, int score, int gold) {
    FILE *file = fopen("players.txt", "r+");
    if (!file) file = fopen("players.txt", "w");

    char line[100], name[50], date[20];
    int existing_score, existing_gold;
    int found = 0;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char today[20];
    strftime(today, sizeof(today), "%Y-%m-%d", t); // تاریخ امروز

    FILE *temp = fopen("temp.txt", "w");

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %d %s", name, &existing_score, &existing_gold, date);
        if (strcmp(name, username) == 0) {
            found = 1;
            fprintf(temp, "%s %d %d %s\n", username, existing_score + score, existing_gold + gold, date);
        } else {
            fprintf(temp, "%s", line);
        }
    }
    if (!found) { // اگر کاربر جدید است، تاریخ امروز را ثبت کند
        fprintf(temp, "%s %d %d %s\n", username, score, gold, today);
    }

    fclose(file);
    fclose(temp);
    remove("players.txt");
    rename("temp.txt", "players.txt");
}

int calculate_days_since_first_game(const char *date_str) {
    struct tm first_game = {0};
    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    sscanf(date_str, "%d-%d-%d", &first_game.tm_year, &first_game.tm_mon, &first_game.tm_mday);
    first_game.tm_year -= 1900; // اصلاح مقدار سال
    first_game.tm_mon -= 1;     // اصلاح مقدار ماه

    time_t first_time = mktime(&first_game);
    double difference = difftime(now, first_time);

    return (int)(difference / (60 * 60 * 24)); // تبدیل ثانیه به روز
}

void display_scoreboard() {
    FILE *file = fopen("players.txt", "r");
    if (!file) {
        printw("No player data found.\n");
        return;
    }

    char username[50], date[20];
    int score, gold;

    while (fscanf(file, "%s %d %d %s", username, &score, &gold, date) != EOF) {
        int days_since = calculate_days_since_first_game(date);
        printw("%-10s  Score: %d  Gold: %d  Playing for: %d days\n", username, score, gold, days_since);
    }

    fclose(file);
}

