
#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../../utils/defines.hpp"
#include "../../start/Core.hpp"


namespace OpMon {
  namespace Model {

    class ResourceLoader{
    public:

      /**
       * Verify that the resource folder exists.
       * @return `true` if it exists; `false` otherwise.
       */
      static bool checkResourceFolderExists();

      /**
       * Load an arbitrary SFML resource
       *
       * @tparam T - the method T::loadFromFile() must exists.
       * @param resource - the resource to load
       * @param path - path of the resource, relative to the resource folder.
       * @param fatal - if true, the program quit if there is an error.
       */
      template<typename T>
      static void load(T &resource, const char *path, bool fatal = false);

      /**
       * Load an array of textures (multiple frames of the same animation).
       *
       * @param container
       * @param path - path relative to the resource folder. It must contains a "%d" , which will be replaced by the
       *    frame number.
       * @param nb_frame - number of texture to load.
       * @param path_offset - by default, the first frame number is 0. If set, the first frame number will be the
       *    offset.
       */
      static void loadTextureArray(sf::Texture container[], const char *path, size_t nb_frame, size_t path_offset = 0);

      /**
       * Load an array of textures (multiple frames of the same animation). See above.
       *
       * The container must be empty.
       */
      static void
      loadTextureArray(std::vector<sf::Texture> &container, const char *path, size_t nb_frame, size_t path_offset = 0);

      static sf::Music *loadMusic(const char *path);

      static std::ifstream loadKeysFile(const char *path);
    };


    template<typename T>
    void ResourceLoader::load(T &resource, const char *path, bool fatal){

      if(!resource.loadFromFile(RESSOURCES_PATH + path)){
        handleError(std::string("Failed to load resource: ") + path, fatal);
      }

    }

  }
}