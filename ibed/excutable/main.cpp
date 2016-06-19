#include "appentry.h"

int main(int argc, char *argv[])
{
    return AppEntry::instance().run(argc, argv);
}
