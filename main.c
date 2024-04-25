#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include "bcdopps.h"

static void button_clicked(GtkWidget *widget, gpointer data) {
    // Handle button click event
    char *label = gtk_button_get_label(GTK_BUTTON(widget));
    g_print("Button clicked: %s\n", label);

    // If the button is a number or operator button
    if (strcmp(label, "=") != 0) {
        // Concatenate the clicked button label to the entry
        const gchar *text = gtk_entry_get_text(GTK_ENTRY(data));
        gchar *new_text = g_strconcat(text, label, NULL);
        gtk_entry_set_text(GTK_ENTRY(data), new_text);
        g_free(new_text);
    } else {
        // If "=" button is clicked, evaluate the expression
        const gchar *expression = gtk_entry_get_text(GTK_ENTRY(data));
        // Convert the expression from string to integer operation
        int a, b;
        char sign;
        sscanf(expression, "%d %c %d", &a, &sign, &b);
        switch (sign) {
            case '+':
                add(a, b);
                break;
            case '-':
                sub(a, b);
                break;
            case '*':
                mul(a, b);
                break;
            case '/':
                divide(a, b);
                break;
            case '^':
                power(a, b);
                break;
            default:
                printf("Please enter correct operation sign \n");
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *entry;
    GtkWidget *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    char *button_labels[16] = {"7", "8", "9", "/", "4", "5", "6", "*", "1", "2", "3", "-", "0", "^", "=", "+"};
    for (int i = 0; i < 16; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), entry);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, i / 4 + 1, 1, 1);
    }

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
