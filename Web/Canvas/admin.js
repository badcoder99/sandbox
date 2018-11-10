(function() {
   $.getJSON("users.json", function(data) {
      $.each(data["users"], function(idx, elem) {
         console.log(elem);
      });
   });
})();

