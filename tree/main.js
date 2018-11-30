//shortcuts & settings
const M = {
  nw : 40, // node width (scale)
  ww : window.innerWidth,
  rotAngle : function(_x1, _y1, _x2, _y2) {
      let dy = _y2-_y1;
      let dx = _x2-_x1;
      return dx > 0 ? Math.atan( dy/dx ) / (Math.PI / 180) : Math.atan( dy/dx ) / (Math.PI / 180) + 180;
    },

  }

document.addEventListener("DOMContentLoaded", function() {

  let renderNode = function(_node, _topPosition, _leftPosition) { 
    let $newNode = document.createElement('div');
    $newNode.className = 'node ' + _node.color;
    $newNode.style.width = M.nw + 'px';
    $newNode.style.height = M.nw + 'px';
    $newNode.style.borderRadius = M.nw + 'px';
    $newNode.style.lineHeight = M.nw + 'px';
    $newNode.style.fontSize = M.nw * 0.75 + 'px';
	$newNode.style.cursor = 'pointer';
    $newNode.innerHTML = _node.key;
    $newNode.id = _node.key;
    $newNode.style.top  = _topPosition  + 'px';
    $newNode.style.left = _leftPosition + 'px';
    $newNode.setAttribute('title', _node.name);
    document.getElementById('conteiner').appendChild($newNode);
  };

  let renderLine = function(_x1, _y1, _x2, _y2) {

    let $newLine = document.createElement('div');
    $newLine.className = 'line';
    $newLine.style.width = Math.sqrt( (_y2 - _y1)*(_y2 - _y1) + (_x2 - _x1)*(_x2 - _x1))+ 'px';
    $newLine.style.top  = _y1  + 'px';
    $newLine.style.left = _x1 + 'px';
    $newLine.style.transform = 'rotate(' + M.rotAngle(_x1, _y1, _x2, _y2) + 'deg)';
    document.getElementById('conteiner').appendChild($newLine);
  }

  let renderTree = function(_tree, _parent, _side) {
    if (!_parent) { //если корень
      renderNode(_tree, 2*M.nw, M.ww/2 - M.nw/2);
    };

    if (_side == 'right') { //если нужно вставить справа
      let parentNodeStyle = getComputedStyle(document.getElementById(_parent.key));
      renderNode(_tree, parseInt(parentNodeStyle.top) + 2*M.nw, parseInt(parentNodeStyle.left) + M.ww/ Math.pow(2, parseInt(parentNodeStyle.top)/(2*M.nw)+1) );
      renderLine(parseInt(parentNodeStyle.left)+M.nw/2, parseInt(parentNodeStyle.top)+M.nw/2, parseInt(parentNodeStyle.left) + M.ww/ Math.pow(2, parseInt(parentNodeStyle.top)/(2*M.nw)+1)+M.nw/2, parseInt(parentNodeStyle.top)+2*M.nw+M.nw/2);
    };

    if (_side == 'left') { //если нужно вставить слева
      let parentNodeStyle = getComputedStyle(document.getElementById(_parent.key));
      renderNode(_tree, parseInt(parentNodeStyle.top) + 2*M.nw, parseInt(parentNodeStyle.left) - M.ww / Math.pow(2, parseInt(parentNodeStyle.top)/(2*M.nw)+1) );
      renderLine(parseInt(parentNodeStyle.left)+M.nw/2, parseInt(parentNodeStyle.top)+M.nw/2, parseInt(parentNodeStyle.left) - M.ww/ Math.pow(2, parseInt(parentNodeStyle.top)/(2*M.nw)+1)+M.nw/2, parseInt(parentNodeStyle.top)+2*M.nw+M.nw/2);
    };

    if (_tree.left) {
      renderTree(_tree.left, _tree, 'left');
    }

    if (_tree.right) {
      renderTree(_tree.right, _tree, 'right');
    }
  };

  renderTree(tree);
});