/*******************************************************************************
 * Name            : main.cc
 * Project         : MIA
 * Module          : main
 * Description     : Entry point for MIA application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include "app/MIA/src/include/mia_app.h"
#include "app/MIA/src/include/mia_filter_manager.h"
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  if (argc == 1) {
    image_tools::MIAApp *app = new image_tools::MIAApp(
        400,
        400,
        "resources/marker.png");
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(400, 400, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
    return 0;
  } else {
    image_tools::MIAApp *app = new image_tools::MIAApp();
    int success = app->Parse(argc, argv);
    delete app;
    return success;
  }
} /** main() */
