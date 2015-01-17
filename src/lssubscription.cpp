#include "lssubscription.hpp"

LSSubscription::LSSubscription(std::string item_t, std::string obj_id, std::vector<std::string> flist) {
  item_type = item_t;
  object_id = obj_id;
  fields= flist;
}

std::string LSSubscription::getItemType() {
  return item_type;
}

std::string LSSubscription::getObjectId(){
  return object_id;
}

std::vector<std::string> LSSubscription::getFields(){
  return fields;
}
