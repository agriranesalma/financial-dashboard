#include <stdio.h>

int main() {
    FILE *file;
    float income, rent, food, transport, entertainment, other;
    float total_expenses, remaining, savings_percent, goal_percent;
    printf("==== SMART FINANCIAL DASHBOARD GENERATOR ====\n\n");
    printf("Enter your monthly income: ");
    scanf("%f", &income);
    printf("Rent: ");
    scanf("%f", &rent);
    printf("Food: ");
    scanf("%f", &food);
    printf("Transport: ");
    scanf("%f", &transport);
    printf("Entertainment: ");
    scanf("%f", &entertainment);
    printf("Other expenses: ");
    scanf("%f", &other);
    printf("Desired savings percentage (example 20 for 20%%): ");
    scanf("%f", &goal_percent);
    total_expenses = rent + food + transport + entertainment + other;
    remaining = income - total_expenses;
    if (income > 0)
        savings_percent = (remaining / income) * 100;
    else
        savings_percent = 0;
    char status[100];
    char advice[200];
    char color[20];

    if (goal_percent <= 0) {
        goal_percent = 20; // Default to 20% if invalid
    }
    if (savings_percent >= goal_percent) {
        sprintf(status, "Meeting / Exceeding Goal (Actual: %.2f%% vs Goal: %.2f%%)", savings_percent, goal_percent);
        sprintf(advice, "Excellent! You're achieving your savings target. Consider investing the surplus.");
        sprintf(color, "green");
    }
    else if (savings_percent >= goal_percent / 2) {
        sprintf(status, "Partially Meeting Goal (%.2f%% vs %.2f%%)", savings_percent, goal_percent);
        sprintf(advice, "You're making progress, but there's room to reach your full goal. Optimize non-essential spending.");
        sprintf(color, "orange");
    }
    else {
        sprintf(status, "Below Goal (%.2f%% vs %.2f%%)", savings_percent, goal_percent);
        sprintf(advice, "Your savings are below target. Review and reduce expenses to meet your goal.");
        sprintf(color, "red");
    }

    float progress = (savings_percent / goal_percent) * 100;
    if (progress > 100) progress = 100;
    if (progress < 0) progress = 0;

    float rent_p = (total_expenses > 0) ? (rent / total_expenses) * 100 : 0;
    float food_p = (total_expenses > 0) ? (food / total_expenses) * 100 : 0;
    float transport_p = (total_expenses > 0) ? (transport / total_expenses) * 100 : 0;
    float entertainment_p = (total_expenses > 0) ? (entertainment / total_expenses) * 100 : 0;
    float other_p = (total_expenses > 0) ? (other / total_expenses) * 100 : 0;

    float cum_rent = rent_p;
    float cum_food = cum_rent + food_p;
    float cum_transport = cum_food + transport_p;
    float cum_entertainment = cum_transport + entertainment_p;
    float cum_other = cum_entertainment + other_p; 

    file = fopen("finance_dashboard.html", "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }
    fprintf(file, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(file, "<meta charset='UTF-8'>\n");
    fprintf(file, "<title>Financial Dashboard</title>\n");
    fprintf(file, "<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&display=swap' rel='stylesheet'>\n");
    fprintf(file, "<style>\n");
    fprintf(file, "body { margin:0; font-family:'Inter', sans-serif; background:#f5f7fa; color:#1f2937; }\n");
    fprintf(file, ".container { max-width:1100px; margin:60px auto; padding:20px; }\n");
    fprintf(file, "h1 { text-align:center; font-size:32px; margin-bottom:50px; font-weight:700; }\n");
    fprintf(file, ".grid { display:grid; grid-template-columns: repeat(4,1fr); gap:25px; }\n");
    fprintf(file, ".card { background:white; padding:30px; border-radius:16px; box-shadow: 0 10px 30px rgba(0,0,0,0.05); transition:0.3s; }\n");
    fprintf(file, ".card:hover { transform: translateY(-4px); }\n");
    fprintf(file, ".card h2 { font-size:13px; text-transform:uppercase; letter-spacing:1px; color:#6b7280; margin-bottom:12px; }\n");
    fprintf(file, ".card p { font-size:28px; font-weight:700; }\n");
    fprintf(file, ".status { margin-top:50px; padding:25px; border-radius:14px; background:white; box-shadow: 0 10px 30px rgba(0,0,0,0.05); border-left:6px solid %s; }\n", color);
    fprintf(file, ".status strong { font-size:18px; display:block; margin-bottom:8px; }\n");
    fprintf(file, ".progress-container { margin-top:40px; }\n");
    fprintf(file, ".progress-bar { width:100%%; height:14px; background:#e5e7eb; border-radius:20px; overflow:hidden; }\n");
    fprintf(file, ".progress-fill { height:100%%; width:%.2f%%; background:%s; border-radius:20px; transition:1s; }\n", progress, color);
    fprintf(file, "table { width:100%%; margin-top:50px; border-collapse: collapse; background:white; border-radius:14px; overflow:hidden; box-shadow: 0 10px 30px rgba(0,0,0,0.05); }\n");
    fprintf(file, "th, td { padding:18px; }\n");
    fprintf(file, "th { text-align:left; font-size:13px; text-transform:uppercase; letter-spacing:1px; background:#f9fafb; color:#6b7280; }\n");
    fprintf(file, "tr:not(:last-child) { border-bottom:1px solid #f0f0f0; }\n");
    fprintf(file, ".pie-container { margin-top:50px; display:flex; flex-direction:column; align-items:center; background:white; padding:30px; border-radius:16px; box-shadow: 0 10px 30px rgba(0,0,0,0.05); }\n");
    fprintf(file, ".pie { width:250px; height:250px; border-radius:50%%; background: conic-gradient(\n");
    fprintf(file, "#3b82f6 0%% %.2f%%,\n", rent_p);
    fprintf(file, "#22c55e %.2f%% %.2f%%,\n", rent_p, cum_food);
    fprintf(file, "#eab308 %.2f%% %.2f%%,\n", cum_food, cum_transport);
    fprintf(file, "#8b5cf6 %.2f%% %.2f%%,\n", cum_transport, cum_entertainment);
    fprintf(file, "#6b7280 %.2f%% 100%%);\n", cum_entertainment);
    fprintf(file, "}\n");
    fprintf(file, ".legend { margin-top:20px; display:flex; flex-direction:column; gap:10px; }\n");
    fprintf(file, ".legend-item { display:flex; align-items:center; font-size:14px; }\n");
    fprintf(file, ".legend-color { width:15px; height:15px; margin-right:10px; border-radius:3px; }\n");
    fprintf(file, "</style>\n</head>\n<body>\n");
    fprintf(file, "<div class='container'>\n");
    fprintf(file, "<h1>Financial Overview</h1>\n");
    fprintf(file, "<div class='grid'>\n");
    fprintf(file, "<div class='card'><h2>Income</h2><p>%.2f</p></div>\n", income);
    fprintf(file, "<div class='card'><h2>Expenses</h2><p>%.2f</p></div>\n", total_expenses);
    fprintf(file, "<div class='card'><h2>Remaining</h2><p>%.2f</p></div>\n", remaining);
    fprintf(file, "<div class='card'><h2>Savings %%</h2><p>%.2f%%</p></div>\n", savings_percent);
    fprintf(file, "</div>\n");
    fprintf(file, "<div class='status'>\n");
    fprintf(file, "<strong>%s</strong>\n", status);
    fprintf(file, "<span>%s</span>\n", advice);
    fprintf(file, "</div>\n");
    fprintf(file, "<div class='progress-container'>\n");
    fprintf(file, "<h3>Progress Towards Savings Goal</h3>\n");
    fprintf(file, "<div class='progress-bar'><div class='progress-fill'></div></div>\n");
    fprintf(file, "</div>\n");
    fprintf(file, "<table>\n");
    fprintf(file, "<tr><th>Category</th><th>Amount</th></tr>\n");
    fprintf(file, "<tr><td>Rent</td><td>%.2f</td></tr>\n", rent);
    fprintf(file, "<tr><td>Food</td><td>%.2f</td></tr>\n", food);
    fprintf(file, "<tr><td>Transport</td><td>%.2f</td></tr>\n", transport);
    fprintf(file, "<tr><td>Entertainment</td><td>%.2f</td></tr>\n", entertainment);
    fprintf(file, "<tr><td>Other</td><td>%.2f</td></tr>\n", other);
    fprintf(file, "</table>\n");
    if (total_expenses > 0) {
        fprintf(file, "<div class='pie-container'>\n");
        fprintf(file, "<h3>Expenses Breakdown</h3>\n");
        fprintf(file, "<div class='pie'></div>\n");
        fprintf(file, "<div class='legend'>\n");
        fprintf(file, "<div class='legend-item'><span class='legend-color' style='background:#3b82f6'></span>Rent (%.2f%%)</div>\n", rent_p);
        fprintf(file, "<div class='legend-item'><span class='legend-color' style='background:#22c55e'></span>Food (%.2f%%)</div>\n", food_p);
        fprintf(file, "<div class='legend-item'><span class='legend-color' style='background:#eab308'></span>Transport (%.2f%%)</div>\n", transport_p);
        fprintf(file, "<div class='legend-item'><span class='legend-color' style='background:#8b5cf6'></span>Entertainment (%.2f%%)</div>\n", entertainment_p);
        fprintf(file, "<div class='legend-item'><span class='legend-color' style='background:#6b7280'></span>Other (%.2f%%)</div>\n", other_p);
        fprintf(file, "</div>\n");
        fprintf(file, "</div>\n");
    }
    fprintf(file, "</div>\n</body>\n</html>");
    fclose(file);
    printf("\nDashboard generated successfully! Open finance_dashboard.html\n");
    return 0;
}
