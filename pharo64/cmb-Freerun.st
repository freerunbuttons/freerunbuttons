Object subclass: #NameOfSubclass
	^ self new 
	currentRun := FreerunRun new .
		ifNil: [ currentContest := self new ]! !
	str := WriteStream on: String new.
	numTimeStampsInRun = 1
	numTimeStampsInRun = 2
	numTimeStampsInRun = 3
	str nextPutAll: '--------' .
	str close .
		, numTimeStampsInRun asString! !
	Transcript cr; show: self htmlText .
 
	html heading:  'Times @ ', self contest stateName  .
	html space.
	"html table
			html tableRow: [ 
 
	html heading: 'Times @ ', self contest stateName  .
	html space.