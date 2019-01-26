  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-47542229-1', 'auto');
  ga('send', 'pageview');

//image
$(function(){
	$('.popup-image').magnificPopup({
		type: 'image'
	});
});

//gallery
$(function(){
$('.parent-container').magnificPopup({
	delegate: 'a',
		type: 'image',
		gallery: { //ギャラリー表示にする
			enabled:true
	}
	});
});

//inline
$(function () {
	$('.popup-modal').magnificPopup({
		type: 'inline',
		preloader: false
	});
	$(document).on('click', '.popup-modal-dismiss', function (e) {
		e.preventDefault();
		$.magnificPopup.close();
	});
});

//retina
$(function () {
$('.retina-modal').magnificPopup({
  type: 'image',

  retina: {
    ratio: 2,
    replaceSrc: function(item, ratio) {
      return item.src.replace(/\.\w+$/, function(m) { return '@2x' + m; });
        }
        }
    });
});

//iframe
$(function(){
	$('.popup-iframe').magnificPopup({
		disableOn: 500,
		type: 'iframe',
		mainClass: 'mfp-fade',
		removalDelay: 200,
		preloader: false,
		fixedContentPos: false
	});
});

//Ajax
$(function(){
$('.ajax-popup').magnificPopup({
		type: 'ajax'
	});
});
