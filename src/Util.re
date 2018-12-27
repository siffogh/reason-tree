[@bs.val] external __dirname: string = "";

let getAbsolutePath = (path: string) => {
  Node.Path.resolve(__dirname, path);
};

let padText = (padding: int, text: string) => {
  String.make(padding, ' ') ++ text;
};

let filterItemsList = (~ignore=?, itemsList: list(Fs.dirent)) => {
  switch (ignore) {
  | None => itemsList
  | Some(nameToIgnore) =>
    itemsList
    |> List.filter(item => !item##isDirectory() || item##name != nameToIgnore)
  };
};

let rec printDir = (~padding: int, ~ignore=?, dirPath: string) => {
  let absolutePath = getAbsolutePath(dirPath);
  let options = Fs.readdirSyncOptions(~withFileTypes=true, ());

  Fs.readdirSync(absolutePath, options)
  |> Array.to_list
  |> filterItemsList(~ignore?)
  |> List.iter((item: Fs.dirent) =>
       if (!item##isDirectory()) {
         {js|📄|js} ++ " " ++ item##name |> padText(padding) |> Js.log;
       } else {
         {js|📁|js} ++ " " ++ item##name |> padText(padding) |> Js.log;
         printDir(
           ~padding=padding + 1,
           ~ignore?,
           absolutePath ++ "/" ++ item##name,
         );
       }
     );
};