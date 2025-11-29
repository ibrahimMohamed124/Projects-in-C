#include <gtk-3.0/gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

GtkWidget *display;

/* تقييم العمليات الرياضية البسيطة بأمان */
double safe_eval(const char *expr, int *error) {
    char *end;
    double result = strtod(expr, &end);
    if (*end == '\0') return result;

    double a, b;
    char op;
    if (sscanf(expr, "%lf %c %lf", &a, &op, &b) == 3) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': if (b == 0) { *error = 1; return 0; }
                      return a / b;
        }
    }
    *error = 1;
    return 0;
}

void set_display(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(display), text);
}

void append_display(const char *text) {
    const char *cur = gtk_entry_get_text(GTK_ENTRY(display));
    if (strcmp(cur, "0") == 0 || strcmp(cur, "Error") == 0)
        gtk_entry_set_text(GTK_ENTRY(display), text);
    else {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%s%s", cur, text);
        gtk_entry_set_text(GTK_ENTRY(display), buffer);
    }
}

void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    const char *cur = gtk_entry_get_text(GTK_ENTRY(display));

    if (strcmp(label, "C") == 0) {
        set_display("0");
        return;
    }

    if (strcmp(label, "⌫") == 0) {
        int len = strlen(cur);
        if (len <= 1 || strcmp(cur, "Error") == 0) set_display("0");
        else {
            char buffer[256];
            strncpy(buffer, cur, len - 1);
            buffer[len - 1] = '\0';
            set_display(buffer);
        }
        return;
    }

    if (strcmp(label, "=") == 0) {
        int err = 0;
        double result = safe_eval(cur, &err);
        if (err) set_display("Error");
        else {
            char buffer[64];
            if (fabs(result - (int)result) < 1e-9)
                sprintf(buffer, "%d", (int)result);
            else
                sprintf(buffer, "%.10g", result);
            set_display(buffer);
        }
        return;
    }

    if (strcmp(label, "±") == 0) {
        if (cur[0] == '-')
            set_display(cur + 1);
        else if (strcmp(cur, "0") != 0 && strcmp(cur, "Error") != 0) {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "-%s", cur);
            set_display(buffer);
        }
        return;
    }

    append_display(label);
}

/* تحميل CSS عصري متوافق مع GTK3 مع foreground أسود */
void load_css(void) {
    GtkCssProvider *css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css,
        "window { background-color: #1a1a1a; }"
        ".display {"
        "    font-family: monospace;"
        "    font-size: 36px;"
        "    background-color: #1a1a1a;"
        "    color: #f0f0f0;"
        "    padding: 15px;"
        "    border-radius: 8px;"
        "    border: none;"
        "}"
        ".btn {"
        "    font-size: 20px;"
        "    padding: 16px;"
        "    border-radius: 12px;"
        "    background-color: #333333;"
        "    color: #000000;"  // foreground أسود
        "    border: none;"
        "}"
        ".btn:hover { background-color: #444444; }"
        ".btn:active { background-color: #222222; }"
        ".op-btn { background-color: #ff9500; color: #000000; }"
        ".op-btn:hover { background-color: #e08700; }"
        ".op-btn:active { background-color: #cc7a00; }"
        ".func-btn { background-color: #505050; color: #000000; }"
        ".func-btn:hover { background-color: #606060; }"
        ".func-btn:active { background-color: #404040; }"
        ".eq-btn { background-color: #007aff; color: #000000; }"
        ".eq-btn:hover { background-color: #0066cc; }"
        ".eq-btn:active { background-color: #0053a3; }"
        ,
        -1, NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

/* إضافة أكثر من class لزر */
void apply_classes(GtkWidget *widget, const char *classes) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    char *copy = g_strdup(classes);
    char *token = strtok(copy, " ");
    while (token != NULL) {
        gtk_style_context_add_class(context, token);
        token = strtok(NULL, " ");
    }
    g_free(copy);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    load_css();

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Modern Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 560);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    display = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(display), 1.0);
    gtk_entry_set_text(GTK_ENTRY(display), "0");
    gtk_editable_set_editable(GTK_EDITABLE(display), FALSE);
    gtk_widget_set_name(display, "display");
    gtk_style_context_add_class(gtk_widget_get_style_context(display), "display");
    gtk_box_pack_start(GTK_BOX(vbox), display, FALSE, FALSE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 12);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    const char *buttons[5][4] = {
        {"C", "⌫", "%", "/"},
        {"7", "8", "9", "*"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "+"},
        {"±", "0", ".", "="}
    };

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 4; c++) {
            const char *label = buttons[r][c];
            GtkWidget *btn = gtk_button_new_with_label(label);
            gtk_widget_set_size_request(btn, 80, 80);

            if (strcmp(label, "=") == 0) {
                apply_classes(btn, "btn eq-btn");
            } else if (strchr("/*-+%", label[0]) != NULL) {
                apply_classes(btn, "btn op-btn");
            } else if (strcmp(label, "C") == 0 || strcmp(label, "⌫") == 0 || strcmp(label, "±") == 0 || strcmp(label, "%") == 0) {
                apply_classes(btn, "btn func-btn");
            } else {
                apply_classes(btn, "btn");
            }

            g_signal_connect(btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), btn, c, r, 1, 1);
        }
    }

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
