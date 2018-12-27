[@bs.deriving abstract]
type readdirSyncOptions = {
  [@bs.optional]
  withFileTypes: bool,
};

type dirent = {
  .
  "name": string,
  [@bs.meth] "isDirectory": unit => bool,
};

[@bs.module "fs"]
external readdirSync: (string, readdirSyncOptions) => array(dirent) = "";