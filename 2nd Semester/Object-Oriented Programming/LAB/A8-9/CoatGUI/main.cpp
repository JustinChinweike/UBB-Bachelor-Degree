#include <QApplication>

#include "AdminModeGUI.h"
#include "UserModeGUI.h"
#include "FileRepository.h"
#include "GUI.h"
#include "test_domain.h"
#include "test_repository.h"
#include "test_service.h"
#include "test_validation.h"
#include "console.h"
#include <repository.h>
#include <service.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    FileRepository repo("text.txt");
    Repository UserRepo;
    Service service(repo, UserRepo);

    Test_Domain testDomain;
    testDomain.TestAllDomain();
    Test_Repository testRepository;
    testRepository.TestAllRepository();
    Test_Validation testValidation;
    testValidation.TestAllValidation();

    //    Console console{service};
    //    console.Start();

    GUI gui{ service };
    gui.setStyleSheet("QMainWindow {background: 'magenta';}");
    gui.show();

    return a.exec();

}