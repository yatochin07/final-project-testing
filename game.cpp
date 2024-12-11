#include <gtk/gtk.h>
#include <cstdlib>
#include <ctime>

// Fungsi untuk memilih pilihan komputer secara acak
const char* get_computer_choice() {
    int choice = rand() % 3;
    switch (choice) {
        case 0: return "Rock";
        case 1: return "Paper";
        case 2: return "Scissors";
        default: return "Rock";
    }
}

// Fungsi untuk menentukan pemenang
const char* determine_winner(const char* player_choice, const char* computer_choice) {
    if (strcmp(player_choice, computer_choice) == 0) {
        return "It's a tie!";
    }

    if ((strcmp(player_choice, "Rock") == 0 && strcmp(computer_choice, "Scissors") == 0) ||
        (strcmp(player_choice, "Paper") == 0 && strcmp(computer_choice, "Rock") == 0) ||
        (strcmp(player_choice, "Scissors") == 0 && strcmp(computer_choice, "Paper") == 0)) {
        return "You win!";
    }

    return "Computer wins!";
}

// Fungsi untuk menangani klik tombol pemain
void on_button_click(GtkButton* button, gpointer user_data) {
    const char* player_choice = (const char*) user_data;
    const char* computer_choice = get_computer_choice();

    // Menentukan hasil pertandingan
    const char* result = determine_winner(player_choice, computer_choice);

    // Mendapatkan widget label untuk menampilkan hasil
    GtkWidget* label_result = gtk_builder_get_object(GTK_BUILDER(user_data), "label_result");

    // Menampilkan hasil
    gchar* result_message = g_strdup_printf("Your choice: %s\nComputer's choice: %s\nResult: %s", player_choice, computer_choice, result);
    gtk_label_set_text(GTK_LABEL(label_result), result_message);
    g_free(result_message);
}

static void on_activate(GtkApplication* app, gpointer user_data) {
    GtkBuilder* builder = gtk_builder_new_from_file("game_suit.glade");
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissors");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Menghubungkan sinyal tombol dengan fungsi on_button_click
    GtkWidget* button_rock = GTK_WIDGET(gtk_builder_get_object(builder, "button_rock"));
    g_signal_connect(button_rock, "clicked", G_CALLBACK(on_button_click), "Rock");

    GtkWidget* button_paper = GTK_WIDGET(gtk_builder_get_object(builder, "button_paper"));
    g_signal_connect(button_paper, "clicked", G_CALLBACK(on_button_click), "Paper");

    GtkWidget* button_scissors = GTK_WIDGET(gtk_builder_get_object(builder, "button_scissors"));
    g_signal_connect(button_scissors, "clicked", G_CALLBACK(on_button_click), "Scissors");

    gtk_widget_show_all(window);
}

int main(int argc, char** argv) {
    srand(time(0)); // Inisialisasi random number generator

    GtkApplication* app = gtk_application_new("com.example.rockpaperscissors", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}