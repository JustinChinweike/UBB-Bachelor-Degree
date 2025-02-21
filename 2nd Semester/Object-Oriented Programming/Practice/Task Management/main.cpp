#include <QApplication>
#include "TaskRepository.h"
#include "TaskController.h"
#include "ProgrammerWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    TaskRepository repo("programmers.txt", "tasks.txt");
    TaskController controller(repo);

    const std::vector<Programmer>& programmers = controller.getProgrammers();
    for (const auto& programmer : programmers) {
        ProgrammerWindow* window = new ProgrammerWindow(controller, programmer);
        window->show();
    }

    int result = app.exec();
    repo.saveTasks("tasks.txt");
    return result;
}
